/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:22:35 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/30 10:50:11 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	free_all(t_data *data)
{
	if (data->paths != 0)
		delete_paths(data);
	if (data->path)
		free(data->path);
	free_env(data);
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
		if (current->value)
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
