/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:37:59 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/09 14:34:47 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	mem_perror(t_data *data)
{
	perror("malloc: ");
	data->exit_code->state = 1; 
}

static void	add_to_env(t_env *env, t_data *data, int i)
{
	t_env	*temp;
	t_env	*temp2;
	char	**temp_arr;

	temp2 = env;
	temp = malloc(sizeof(t_env));
	if (!temp)
		mem_perror(data);
	temp_arr = ft_split(data->envp[i], '=');
	if (!temp_arr)
		mem_perror(data);
	temp->key = ft_strdup(temp_arr[0]);
	if (!temp->key)
		mem_perror(data);
	temp->value = ft_strdup(temp_arr[1]);
	if (!temp->value)
		mem_perror(data);
	free_array(temp_arr);
	temp->next = NULL;
	while (temp2->next != NULL)
		temp2 = temp2->next;
	temp2->next = temp;
}

void	create_env_list(t_data *data, t_env *env)
{
	char	**temp_arr;
	int		i;

	i = 1;
	env = malloc(sizeof(t_env));
	if (!env)
		mem_perror(data);
	temp_arr = ft_split(data->envp[0], '=');
	if (!temp_arr)
		mem_perror(data);
	env->key = ft_strdup(temp_arr[0]);
	if (!env->key)
		mem_perror(data);
	env->value = ft_strdup(temp_arr[1]);
	if (!env->value)
		mem_perror(data);
	free_array(temp_arr);
	env->next = NULL;
	while (i < ft_arraylen(data->envp))
	{
		add_to_env(env, data, i);
		i++;
	}
	data->env_list = env;
}

static void	print_env(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr != NULL)
	{
		if (ptr->key && ptr->value)
			printf("%s=%s\n", ptr->key, ptr->value);
		ptr = ptr->next;
	}
}

void	env_cmd(t_data *data)
{
	print_env(data->env_list);
	data->exit_code->state = 0;
}
