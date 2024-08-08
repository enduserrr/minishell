/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:48:36 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/08 11:56:48 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void write_fd(int fd, const char *color, const char *text)
{
    write(fd, color, ft_strlen(color));
    write(fd, text, ft_strlen(text));
    write(fd, RESET, ft_strlen(RESET));
}

int	ft_arraylen(char **arr)
{
	int	len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}

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
