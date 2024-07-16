/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:39:40 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/15 13:39:44 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void get_path(t_tools *tools, char *cmd)
{
    int i;
    char *path;
    char *temp;

    i = 0;
    temp = ft_strjoin("/", cmd);
    while (tools->paths[i] != NULL)
    {
        path = ft_strjoin(tools->paths[i], temp);
        if (access(path, F_OK) == 0)
        { 
            free(temp);
            tools->valid_path = path;
            return ;
        }
        free(path);
        i ++;
    }
    tools->valid_path = NULL;
    free(temp);
}

void execute_one_cmd(t_tools *tools)
{
    if (tools->valid_path != NULL)
    {
        if(execve(tools->valid_path, tools->split_rl, NULL) != 0)
            perror("eitoimi\n");
    }
}

void simple_arg(t_tools *tools)
{
    pid_t   p1;
    int     status;

    status = 0;
    get_path(tools, tools->split_rl[0]);
    p1 = fork();
    if(p1 == -1)
        perror("fork");
    if (p1 == 0)
        execute_one_cmd(tools);
    waitpid(p1, &status, 0);
    free(tools->valid_path);
}

void execution(t_tools *tools)
{
    //if (tools->split_rl[2] == NULL)
    simple_arg(tools);
}