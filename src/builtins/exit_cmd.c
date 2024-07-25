/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:38:10 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/20 22:38:13 by eleppala         ###   ########.fr       */
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

void	exit_cmd(t_data *data)
{
	int	flag;

	flag = 0;
	data->exit_code = 0;
	printf("exit");
	if (data->cmds->av[1] != NULL)
	{
		data->exit_code = ft_atoi(data->cmds->av[1]);
		if (!data->exit_code && data->cmds->av[1][0] != '0')
		{
			printf(": %s: numeric argument required", data->cmds->av[1]);
			data->exit_code = 255;
		}
		else if (data->exit_code && data->cmds->av[2])
		{
			printf(": too many arguments");
			flag = -1;
		}
	}
	printf("\n");
	if (flag == 0)
	{
		free_all(data);
		exit(data->exit_code);
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
