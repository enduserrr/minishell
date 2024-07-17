/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:56:00 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/16 18:56:03 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void child(t_tools *tools, int i, int *prev_fd, int *fd)
{
    if (i == 0)
    {
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1)
            perror("dup1\n");
        close(fd[1]);
        execute_one_cmd(tools, 0);
    }
    else if (i == tools->pipe_amount)
    {
        close(prev_fd[1]);
        if (dup2(prev_fd[0], STDIN_FILENO) == -1)
            perror("dup2");
        close(prev_fd[0]);
        execute_one_cmd(tools, i * 3);
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
        execute_one_cmd(tools, i * 3);
    }
}

void create_pids(t_tools *tools)
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
    tools->pid_arr = malloc((tools->pipe_amount + 1)* sizeof(pid_t));
    if (!tools->pid_arr)
        perror("malloc");
    while(i <= tools->pipe_amount)
    {
        if (i < tools->pipe_amount)
            pipe(fd);
        pid = fork();
        if (pid < 0)
            perror("fork");
        else if (pid == 0)
            child(tools, i, prev_fd, fd);
        else
        {
            tools->pid_arr[i] = pid;
            if (prev_fd[0] != -1)
            {
                close(prev_fd[0]);
                close(prev_fd[1]);
            }
            if (i < tools->pipe_amount)
            {
                prev_fd[0] = fd[0];
                prev_fd[1] = fd[1];
            }
        }
        i ++;
    }
    i = 0;
    while(i <= tools->pipe_amount)
    {
        waitpid(tools->pid_arr[i], &status, 0);
        i ++;
    }
    free(tools->pid_arr);
}

int pipes_in_prompt(t_tools *tools)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    while(tools->split_rl[i])
    {
        if (ft_strncmp(tools->split_rl[i], "|", 1) == 0)
            flag ++;
        i ++;
    }
    tools->pipe_amount = flag;
    return (flag);
}

