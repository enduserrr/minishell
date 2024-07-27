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

void first_child(t_data *data, int i, int *fd)
{
    close(fd[0]);
    check_redir(data, i);
    if (dup2(fd[1], STDOUT_FILENO) == -1)
        perror("dup1\n");
    close(fd[1]);
    execute_cmd(data, i);
}

void last_child(t_data *data, int i, int *prev_fd)
{
    close(prev_fd[1]);
    if (check_redir(data, i) != 1)
    {
        if (dup2(prev_fd[0], STDIN_FILENO) == -1)
            perror("dup2");
    }
    close(prev_fd[0]);
    execute_cmd(data, i);
}

void childs(t_data *data, int i, int *prev_fd, int *fd)
{
    if (i == 0)
    {
        first_child(data, i, fd);
    }
    else if (i == data->pipe_amount)
    {
        last_child(data, i, prev_fd);
    }
    else
    {
        close(prev_fd[1]);
        if (check_redir(data, i) != 1)
        {
            if (dup2(prev_fd[0], STDIN_FILENO) == -1)
                perror("dup 3");
        }
        close(prev_fd[0]);
        close(fd[0]);
        if (check_redir(data, i) != 2)
        {
            if(dup2(fd[1], STDOUT_FILENO) == -1)
                perror("dup");
        }
        execute_cmd(data, i);
    }
}

void    wait_childs(t_data *data)
{
    int i;
    int status;

    i = 0;
    status = 0;
    while(i <= data->pipe_amount)
    {
        waitpid(data->pid_arr[i], &status, 0);
        i ++;
    }
    free(data->pid_arr);
}

void create_pids(t_data *data)
{
    int     i;
    int     prev_fd[2];
    int     fd[2];

    i = 0;
    prev_fd[0] = -1;
    prev_fd[1] = -1;
    data->pid_arr = malloc((data->pipe_amount + 1)* sizeof(pid_t));
    if (!data->pid_arr)
        perror("malloc");
    while(i <= data->pipe_amount)
    {
        if (i < data->pipe_amount)
            pipe(fd);
        data->pid_arr[i] = fork();
        if (data->pid_arr[i] < 0)
            perror("fork");
        else if (data->pid_arr[i] == 0)
            childs(data, i, prev_fd, fd);
        else
            next_pipe(data, prev_fd, fd, i);
        i ++;
    }
    wait_childs(data);
}
