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

/*
 * Command env outputs list of environment variables
 */

void	env_cmd(t_tools *tools)
{
	int	i;

	i = 0;
	while (tools->envp[i])
	{
		printf("%s\n", tools->envp[i]);
		i++;
	}
}
