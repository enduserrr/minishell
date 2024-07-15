/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:38:10 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/15 09:05:12 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
/*
 * Command exit frees everything and closes program
 * Exit with no options - but theres no mention about arguments..
 * exit "sddsss"  --> exit: numeric argument required
 * exit 6 "ffff" --> exit: too many arguments --> Continue program
 * exit 6  --> exits with exit code 6
 */

void	exit_cmd(t_tools *tools)
{
	int	flag;

	flag = 0;
	tools->exit_code = 0;
	printf("exit");
	if (tools->split_rl[1] != NULL)
	{
		tools->exit_code = ft_atoi(tools->split_rl[1]);
		if (!tools->exit_code && tools->split_rl[1][0] != '0')
		{
			printf(": %s: numeric argument required", tools->split_rl[1]);
			tools->exit_code = 255;
		}
		else if (tools->exit_code && tools->split_rl[2])
		{
			printf(": too many arguments");
			flag = -1;
		}
	}
	printf("\n");
	if (flag == 0)
	{
		free_all(tools);
		exit(tools->exit_code);
	}
}

/*
 * DELETE THIS
 *
 * exit command exits and frees everything (might need updates with freeing later)
 * exit can take argument, but it needs to be numeric
 * 	- if non numeric outputs error and exits
 * 	- if first is numeric and there are more args outputs "too many args"
 * 
 * FEATURES:
 * 								
 * 	Command:					output:						exit_code:	result:
 *  exit without args			"Exit"						0			exit
 * 	exit with numeric arg		"Exit"						(arg)		exit
 *  exit with multiple args		"Too many arguments"		1			continue 
 * 	exit with nonnumeric arg	"Numeric arg required.." 	255			exit
 * 
 */
