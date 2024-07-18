/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:31:39 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/21 15:31:45 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	remove_variable(t_tools *tools, int i)
{
	t_env	*temp;
	t_env	*temp2;

	temp = tools->env_list;
	temp2 = tools->env_list->next;
	if (ft_strncmp(tools->split_rl[i], temp->key, ft_strlen(temp->key)) == 0)
	{
		temp = free_node(temp);
		tools->env_list = temp2;
		return ;
	}
	while (temp->next != NULL)
	{
		if (ft_strncmp(tools->split_rl[i], temp2->key,
				ft_strlen(temp2->key)) == 0)
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

void	unset_cmd(t_tools *tools)
{
	int	i;

	i = 1;
	tools->exit_code = 0;
	if (!tools->split_rl[1])
		return ;
	while (tools->split_rl[i] != NULL)
	{
		if (validate_arg(tools->split_rl[i]) == 0)
		{
			if (ft_strncmp(tools->split_rl[i], "PATH", 4) == 0)
				delete_paths(tools);
			remove_variable(tools, i);
		}
		i++;
	}
}

/*
 * DELETE THIS
 *
 * unset will delete given argument from env_list
 *
 * unset without argument does nothing
 * argument needs to start with alphabet
 *  - if not outputs error, if not outputs error
 * 	- with multiple args deletes all matching key/value pairs from env_list
 *  - if multiple args includes one unvalid arg it shows error,
	but still does the job.
 */