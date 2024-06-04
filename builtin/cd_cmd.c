/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:37:04 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/20 22:37:15 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	cd_error(t_tools *tools)
{
	perror("cd");
	tools->exit_code = 1;
}

void	trim_last(t_tools *tools, char *pwd)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(pwd);
	while (len > 1)
	{
		if (pwd[len] == '/')
			break ;
		len--;
	}
	tools->prev_path = malloc(len * sizeof(char));
	if (!tools->prev_path)
		perror("malloc: ");
	while (i < len)
	{
		tools->prev_path[i] = pwd[i];
		i++;
	}
	tools->prev_path[i] = '\0';
}

static int	get_home(t_tools *tools)
{
	t_env *temp;

	temp = tools->env_list;
	while(temp != NULL)
	{
		if(ft_strncmp(temp->key, "HOME", 4) == 0 && temp->value !=  NULL)
		{
			if (chdir(temp->value) == -1)
			{
				perror("cd");
				return (1);
			}
			return (0);
		}
		temp = temp->next;
	}
	printf("cd: HOME not set\n");
	return (1);
}

void	cd_cmd(t_tools *tools)
{
	char	*old_pwd;

	tools->exit_code = 0;
	old_pwd = getcwd(NULL, 0);
	if (tools->split_rl[1] == NULL)
		tools->exit_code = get_home(tools);
	else if (ft_strncmp(tools->split_rl[1], "..", 2) == 0)
	{
		trim_last(tools, old_pwd);
		if (chdir(tools->prev_path) == -1)
			cd_error(tools);
		tools->prev_path = NULL;
	}
	else
	{
		if (chdir(tools->split_rl[1]) == -1)
			cd_error(tools);
	}
	update_pwds(tools, old_pwd);
}

/*
 * DELETE THIS
 *
 *  works already similar as regular cd with limits of subject:
 * 	- updates env_list: PWD && OLDPWD on every movement
 *  - outputs correct errors in error cases
 * 
 * 
 *  FEATURES: 
 * 	cd without args 				--> home 							--> exit_code 0
 * 	cd without args (unset HOME)	--> "home not set"  				--> exit_code 1
 *  cd without args (HOME=badpath)	--> "no such file or dir"			--> exit_code 1
 *  cd with .. 						--> previous_directory from path	--> exit_code 0
 *  cd with <dir_name>  			--> moves to that dir				--> exit_code 1
 *  cd /path/paths/pathsss/ 		--> moves to end of path 			--> exit_code 0
 * 
 * 
 * exit_code:
 * in most cases its going to be 0 
 *  - set it to zero in beginning and modify only when needed
 * 
 * 
 */
