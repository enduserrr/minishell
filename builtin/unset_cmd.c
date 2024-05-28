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

int		keylen(t_tools *tools)
{
	int len;

	len = 0;
	while(tools->split_rl[1][len] != '\0')
	{
		if(tools->split_rl[1][len] == '=')
			break ;
		len ++;
	}
	return (len);
}

static t_env	*free_node(t_env *node)
{
	free(node->key);
	node->key = NULL;
	free(node->value);
	node->value = NULL;
	free(node);
	node = NULL;
	return node; 
}

void	remove_variable(t_tools *tools)
{
	t_env *temp;
	t_env *temp2;

	temp = tools->env_list;
	temp2 = tools->env_list->next;
	while(temp->next != NULL)
	{
		if (ft_strncmp(temp2->key, tools->split_rl[1], keylen(tools)) == 0)
		{		
			if (temp2->next == NULL)
			{
				temp2 = free_node(temp2);
				temp->next = NULL;
				break ; 
			}
			temp->next = temp2->next;
			temp2 = free_node(temp2);
			break ;
		}	
		temp = temp->next;
		temp2 = temp2->next; 
	}
}

void	unset_cmd(t_tools *tools)
{
	if (!tools->split_rl[1])
		return ;
	if (tools->split_rl[1] != NULL && !tools->split_rl[2])
		remove_variable(tools);
}