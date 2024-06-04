/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:37:44 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/20 22:37:47 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_cmd(t_tools *tools)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (tools->split_rl[1] != NULL && ft_strncmp(tools->split_rl[1], "-n",
			2) == 0)
	{
		flag = 1;
		i++;
	}
	while (tools->split_rl[i])
	{
		printf("%s", tools->split_rl[i]);
		i++;
	}
	if (flag == 0)
		printf("\n");
	tools->exit_code = 0;
}

/*
 * DELETE THIS
 * 
 * echo without args	--> "emptyline\n"
 * echo "hello"			--> "hello\n"
 * echo	-n 				--> "emptyline" (without new line)
 * echo -n "hello"		--> "hello" (without new line)
 *
 * 
 * 
 *  TEST THESE: 
 *  - echo hello $? <--> echo $? hello 
 *  	- differrent exit_code 
 * 
 */
