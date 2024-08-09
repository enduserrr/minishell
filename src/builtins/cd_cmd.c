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

static void	cd_error(t_data *data, char *old_pwd)
{
	perror("cd");
	free(old_pwd);
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
	data->prev_path = malloc(len + 1 * sizeof(char));
	if (!data->prev_path)
		perror("malloc: ");
	while (i < len)
	{
		data->prev_path[i] = pwd[i];
		i++;
	}
	data->prev_path[i] = '\0';
}

static void	cd_home(t_data *data, char *old_pwd)
{
	t_env	*temp;

	temp = data->env_list;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, "HOME", 4) == 0 && temp->value != NULL)
		{
			if (chdir(temp->value) == -1)
			{
				cd_error(data, old_pwd);
				return ;
			}
			update_pwds(data, old_pwd);
			data->exit_code->state = 1;
			return ;
		}
		temp = temp->next;
	}
	printf("cd: HOME not set\n");
	data->exit_code->state = 1;
}

static void	cd_prev(t_data *data, char *old_pwd)
{
	trim_last(data, old_pwd);
	if (chdir(data->prev_path) == -1)
		cd_error(data, old_pwd);
	else
	{
		update_pwds(data, old_pwd);
		data->exit_code->state = 0;
	}
	free(data->prev_path);
	data->prev_path = NULL;
}

void	cd_cmd(t_data *data)
{
	char	*old_pwd;

	old_pwd = NULL;
	data->exit_code->state = 0;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		old_pwd = ft_get_cwd(data->env_list);
		if (!old_pwd)
			return ;
	}
	if (data->cmds->av[1] == NULL)
		cd_home(data, old_pwd);
	else if (ft_strncmp("..", data->cmds->av[1],
			2) == 0 && ft_strlen(data->cmds->av[1]) < 3)
		cd_prev(data, old_pwd);
	else
	{
		if (chdir(data->cmds->av[1]) == -1)
			cd_error(data, old_pwd);
		else
			update_pwds(data, old_pwd);
	}
}
