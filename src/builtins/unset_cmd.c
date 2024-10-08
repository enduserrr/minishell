/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:31:39 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/09 14:32:41 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
 *  - unset works now with multiple arguments
 *  - unset has argument validation
 */

static int	validate_arg(char *str)
{
	if (ft_isalpha(str[0]) == 0)
	{
		printf("unset: `%s': is not a valid identifier\n", str);
		return (-1);
	}
	return (0);
}

static t_env	*free_node(t_env *node)
{
	free(node->key);
	node->key = NULL;
	free(node->value);
	node->value = NULL;
	free(node);
	node = NULL;
	return (node);
}

static int	first_node(t_data *data, t_env *temp, t_env *temp2, int i)
{
	if (ft_strncmp(data->cmds->av[i], temp->key,
			ft_strlen(data->cmds->av[i])) == 0)
	{
		temp = free_node(temp);
		data->env_list = temp2;
		return (0);
	}
	return (1);
}

static void	remove_variable(t_data *data, int i)
{
	t_env	*temp;
	t_env	*temp2;

	temp = data->env_list;
	temp2 = data->env_list->next;
	if (first_node(data, temp, temp2, i) == 0)
		return ;
	while (temp->next != NULL)
	{
		if (ft_strncmp(data->cmds->av[i], temp2->key,
				ft_strlen(data->cmds->av[i])) == 0)
		{
			if (temp2->next == NULL)
			{
				temp2 = free_node(temp2);
				temp->next = NULL;
				break ;
			}
			temp->next = temp2->next;
			temp2 = free_node(temp2);
		}
		temp = temp->next;
		temp2 = temp->next;
	}
}

void	unset_cmd(t_data *data)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	data->exit_code->state = 0;
	if (!data->cmds->av[1])
		return ;
	while (data->cmds->av[i] != NULL)
	{
		len = ft_strlen(data->cmds->av[i]);
		if (validate_arg(data->cmds->av[i]) == 0)
		{
			if (data->paths && ft_strncmp("PATH", data->cmds->av[i], len) == 0)
				delete_paths(data);
			remove_variable(data, i);
		}
		i++;
	}
}
