/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:52:09 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/02 10:13:00 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	delete_paths(t_data *data)
{
	free_array(data->paths);
	data->paths = NULL;
}

void	create_paths(t_data *data)
{
	t_env	*temp;

	temp = data->env_list;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, "PATH", 4) == 0)
		{
			data->paths = ft_split(temp->value, ':');
			break ;
		}
		temp = temp->next;
	}
}
