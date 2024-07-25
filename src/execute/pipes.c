/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:56:00 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/25 10:24:27 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void child(t_data *data, int i, int *prev_fd, int *fd)
{
    if (i == 0)
    {
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1)
            perror("dup1\n");
        close(fd[1]);
        execute_cmd(data, i);
    }
    else if (i == data->pipe_amount)
    {
        close(prev_fd[1]);
        if (dup2(prev_fd[0], STDIN_FILENO) == -1)
            perror("dup2");
        close(prev_fd[0]);
        execute_cmd(data, i);
    }
    else
    {
        close(prev_fd[1]);
        if (dup2(prev_fd[0], STDIN_FILENO) == -1)
            perror("dup 3");
        close(prev_fd[0]);
        close(fd[0]);
        if(dup2(fd[1], STDOUT_FILENO) == -1)
            perror("dup");
        execute_cmd(data, i);
    }
}

void create_pids(t_data *data)
{
    int     i;
    pid_t   pid;
    int     prev_fd[2];
    int     fd[2];
    int     status;

    i = 0;
    status = 0;
    prev_fd[0] = -1;
    prev_fd[1] = -1;
    data->pid_arr = malloc((data->pipe_amount + 1)* sizeof(pid_t));
    if (!data->pid_arr)
        perror("malloc");
    while(i <= data->pipe_amount)
    {
        if (i < data->pipe_amount)
            pipe(fd);
        pid = fork();
        if (pid < 0)
            perror("fork");
        else if (pid == 0)
            child(data, i, prev_fd, fd);
        else
        {
            data->pid_arr[i] = pid;
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
        i ++;
    }
    i = 0;
    while(i <= data->pipe_amount)
    {
        waitpid(data->pid_arr[i], &status, 0);
        i ++;
    }
    free(data->pid_arr);
}

int pipes_in_prompt(t_data *data)
{
    t_cmd   *temp;
    int     flag;

    temp = data->cmds;
    flag = 0;
    while(temp->next != NULL)
    {
        temp = temp->next;
        flag ++;
    }
    data->pipe_amount = flag;
    return (flag);
}

