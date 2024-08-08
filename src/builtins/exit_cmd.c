/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:38:10 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/08 11:49:35 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	exit_cmd(t_data *data)
{
	int	flag;

	flag = 0;
	data->exit_code->state = 0;
	printf("exit");
	if (data->cmds->av[1] != NULL)
	{
		data->exit_code->state = ft_atoi(data->cmds->av[1]);
		if (!data->exit_code->state && data->cmds->av[1][0] != '0')
		{
			printf(": %s: numeric argument required", data->cmds->av[1]);
			data->exit_code->state = 255;
		}
		else if (data->exit_code->state && data->cmds->av[2])
		{
			printf(": too many arguments");
			flag = -1;
		}
	}
	printf("\n");
	if (flag == 0)
	{
		free_all(data);
		exit(data->exit_code->state);
	}
}
