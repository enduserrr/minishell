/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:22:35 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/23 21:22:38 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	free_all(t_data *data)
{
	if (data->path != 0)
		free(data->path);
	free_env(data);
	free_commands(data->cmds);
	//free_history(data);
}

void	free_env(t_data *data)
{
	t_env	*current;
	t_env	*temp;

	current = data->env_list;
	while (current != NULL)
	{
		temp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = temp;
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}