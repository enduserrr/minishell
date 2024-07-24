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

#include "../../incs/minishell.h"

static void	exit_status(t_data *data, int i)
{
	//in own function because there might be more pieces to come....
	//$?$? = 00, pas$?ka  = pas0ka 
	(void)i;
	printf("%d", data->exit_code);
}

void	echo_cmd(t_data *data)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (data->cmds->av[1] != NULL && 
		ft_strncmp(data->cmds->av[1], "-n", 2) == 0)
	{
		flag = 1;
		i++;
	}
	while (data->cmds->av[i])
	{
		if (i > 1)
			printf(" ");
		if (ft_strncmp(data->cmds->av[i], "$?", 2) == 0)
			exit_status(data, i);
		else
			printf("%s", data->cmds->av[i]);
		i++;
	}
	if (flag == 0)
		printf("\n");
	data->exit_code = 0;
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
 *
 */
