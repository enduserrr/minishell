/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:30:17 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/23 22:30:20 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	is_builtin(t_data *data)
{
	size_t len;

	len = ft_strlen(data->cmds->av[0]);
	if (ft_strncmp(data->cmds->av[0], "exit", len) == 0)
		return (exit_cmd(data), 1);
    if (ft_strncmp(data->cmds->av[0], "cd", len) == 0)
		return (cd_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "env", len) == 0)
		return (env_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "echo", len) == 0)
		return (echo_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "pwd", len) == 0)
		return (pwd_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "unset", len) == 0)
		return (unset_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "export", len) == 0)
		return (export_cmd(data), 1);
	return (0);
}
void	update_pwds(t_data *data, char *old_pwd)
{
	char    *pwd;
    t_env   *temp;

	pwd = getcwd(NULL, 0);
    temp = data->env_list;
	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->key, "OLDPWD", 6) == 0)
		{
			free(temp->value);
			temp->value = NULL;
			temp->value = old_pwd;
		}
		else if (ft_strncmp(temp->key, "PWD", 3) == 0)
		{
			free(temp->value);
			temp->value = NULL;
			temp->value = pwd;
		}
		temp = temp->next;
	}
}
