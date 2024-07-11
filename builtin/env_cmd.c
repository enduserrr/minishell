/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:37:59 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/20 22:38:02 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env(t_env *env)
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

void	env_cmd(t_tools *tools)
{
	print_env(tools->env_list);
	tools->exit_code = 0;
}

/*
 * DELETE THIS
 *
 * outputs env variables
 * outputs only variables that has key and value.
 * 
 */