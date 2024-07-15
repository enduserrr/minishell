/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:01:44 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/22 14:01:47 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(t_tools *tools)
{
	t_env	*current;
	t_env	*temp;

	current = tools->env_list;
	while (current != NULL)
	{
		temp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = temp;
	}
}

void	add(t_env *env, t_tools *tools, int i)
{
	t_env	*temp;
	t_env	*temp2;
	char	**temp_arr;

	temp2 = env;
	temp = malloc(sizeof(t_env));
	if (!temp)
		perror("malloc");
	temp_arr = ft_split(tools->envp[i], '=');
	temp->key = ft_strdup(temp_arr[0]);
	temp->value = ft_strdup(temp_arr[1]);
	free_array(temp_arr);
	temp->next = NULL;
	while (temp2->next != NULL)
		temp2 = temp2->next;
	temp2->next = temp;
}

void	create_env_list(t_tools *tools)
{
	t_env	*env;
	char	**temp_arr;
	int		i;

	i = 1;
	env = malloc(sizeof(t_env));
	if(!env)
		perror("malloc");
	temp_arr = ft_split(tools->envp[0], '=');
	env->key = ft_strdup(temp_arr[0]);
	env->value = ft_strdup(temp_arr[1]);
	free_array(temp_arr);
	env->next = NULL;
	while (i < ft_arraylen(tools->envp))
	{
		add(env, tools, i);
		i++;
	}
	tools->env_list = env;
}

/*
 * DELETE THIS
 *
 * Create env_list in start of the run
 * env_list is a linked list and it starts from tools->env_list
 * env_list will be filled with environment variables (key/value pairs)
 *	- MAIL=student@student.hive.fi
 */