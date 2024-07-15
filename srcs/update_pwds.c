/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:21:05 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/28 09:21:18 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_old_pwd(char *old_pwd, t_tools *tools)
{
	t_env	*temp;

	temp = tools->env_list;
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

static void	update_pwd(char *pwd, t_tools *tools)
{
	t_env	*temp;

	temp = tools->env_list;
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
}

void	update_pwds(t_tools *tools, char *old_pwd)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	update_pwd(pwd, tools);
	update_old_pwd(old_pwd, tools);
}