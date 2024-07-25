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

/*
static void	update_old_pwd(char *old_pwd, t_data *data)
{
	t_env	*temp;

	temp = data->env_list;
	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->key, "OLDPWD", 6) == 0)
		{
			free(temp->value);
			temp->value = NULL;
			temp->value = old_pwd;
		}
		temp = temp->next;
	}
}

static void	update_pwd(char *pwd, t_data *data)
{
	t_env	*temp;

	temp = data->env_list;
	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->key, "PWD", 3) == 0)
		{
			free(temp->value);
			temp->value = NULL;
			temp->value = pwd;
		}
		temp = temp->next;
	}
}*/

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
