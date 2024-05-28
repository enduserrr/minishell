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

void	remove_variable(t_tools *tools)
{
	t_env *temp;
	//t_env *temp2;

	temp = tools->env_list;
	while(temp->next != NULL)
	{
		if (ft_strncmp(temp->key, tools->split_rl[1], keylen(tools)) == 0)
		{		
			//temp2 = temp;
			temp->key = temp->next->key;
			temp->value = temp->next->value;
			temp->next->next = temp->next->next->next;
			temp = temp->next;
		}
		temp = temp->next;
	}

}

void	unset_cmd(t_tools *tools)
{
	remove_variable(tools);
}