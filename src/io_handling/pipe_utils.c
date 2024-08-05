/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:29:44 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/05 15:32:24 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int pipes_in_prompt(t_data *data)
{
    t_cmd   *temp;
    int     flag;

    temp = data->cmds;
    flag = 0;
    while(temp->next)
    {
        flag++;
        temp = temp->next;
        // flag ++;
    }
    data->pipe_amount = flag;
    return (flag);
}

void next_pipe(t_data *data, int *prev_fd, int *fd, int i)
{
    if (prev_fd[0] != -1)
    {
        close(prev_fd[0]);
        close(prev_fd[1]);
    }
    if (i < data->pipe_amount)
    {
        prev_fd[0] = fd[0];
        prev_fd[1] = fd[1];
    }
}
