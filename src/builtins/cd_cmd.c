/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:37:04 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/02 11:01:05 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	cd_error(t_data *data)
{
	perror("cd");
	data->exit_code->state = 1;
}

static void	trim_last(t_data *data, char *pwd)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(pwd);
	while (len > 1)
	{
		if (pwd[len] == '/')
			break ;
		len--;
	}
	data->prev_path = malloc(len + 1* sizeof(char));
	if (!data->prev_path)
		perror("malloc: ");
	while (i < len)
	{
		data->prev_path[i] = pwd[i];
		i++;
	}
	data->prev_path[i] = '\0';
}

static int	cd_home(t_data *data)
{
	t_env	*temp;

	temp = data->env_list;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, "HOME", 4) == 0 && temp->value != NULL)
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

void	cd_cmd(t_data *data)
{
	char	*old_pwd;

	old_pwd = NULL;
	data->exit_code->state = 0;
	old_pwd = getcwd(NULL, 0);
	if(!old_pwd)
		perror("cwd");
	if (data->cmds->av[1] == NULL)
		data->exit_code->state = cd_home(data);
	else if (ft_strncmp(data->cmds->av[1], "..", 2) == 0)
	{
		trim_last(data, old_pwd);
		if (chdir(data->prev_path) == -1)
			cd_error(data);
		free(data->prev_path);
		data->prev_path = NULL;
	}
	else
	{
		if (chdir(data->cmds->av[1]) == -1)
			cd_error(data);
	}
	update_pwds(data, old_pwd);
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
 *
 *  Command:						output/result:						Exit_code:
 * 	cd without args 				move to: home 						0
 * 	cd without args (unset HOME)	"home not set"  					1
 *  cd without args (HOME=badpath)	"no such file or dir"				1
 *  cd with .. 						move to: prev dir from path			0
 *  cd with <dir_name>  			moves to: that dir					1
 *  cd/path/paths/pathsss/ 			moves to: end of path 				0
 *
 *  Things to consider:
 *  - what happens if you delete current file from another terminal window
 *  - do you need to handle ../path
 *
 */
