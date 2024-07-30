/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:39:40 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/30 09:43:29 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void get_path(t_data *data, t_cmd *cmd)
{
    int i;
    char *path;
    char *temp;

    i = 0;
    temp = ft_strjoin("/", cmd->av[0]);
    if (data->paths == NULL)
    {
        cmd->path = NULL;
        return ;
    }
    while (data->paths[i] != NULL)
    {
        path = ft_strjoin(data->paths[i], temp);
        if (access(path, F_OK) == 0)
        {
            free(temp);
            cmd->path = path;
            return ;
        }
        free(path);
        i ++;
    }
    cmd->path = NULL;
    free(temp);
}

void execute_cmd(t_data *data, int i)
{
    t_cmd   *temp;

    temp = data->cmds;
    while(i > 0)
    {
        //printf("i %d, temp: %s\n", i, temp->av[0]);
        temp = temp->next;
        i --;
    }
    get_path(data, temp);
    //printf("\npath-->%s\n", temp->path);
    //printf("path: [%s], cmds: [%s] [%s]\n", temp->path, temp->av[0], temp->av[1]);
    if (temp->path != NULL)
    {
        if(execve(temp->path, temp->av, NULL) != 0)
            perror("eitoimi\n");
    }
    else
    {
        printf("%s: command not found\n", data->cmds->av[0]);
        data->exit_code = 127;
        //if (data->pipe_amount > 0)
        exit(data->exit_code);
    }
}

void simple_arg(t_data *data)
{
    pid_t   p1;
    int     status;

    status = 0;
    p1 = fork();
    if(p1 == -1)
        perror("fork");
    if (p1 == 0)
    {
        check_redir(data, 0);
        execute_cmd(data, 0);
    }
    waitpid(p1, &status, 0);
}

void execution(t_data *data)
{
    //redir(data);
    if (pipes_in_prompt(data) == 0)
    {
        if (is_builtin(data) == 0)
            simple_arg(data);
    }
    if (pipes_in_prompt(data) != 0)
        create_pids(data);
}
