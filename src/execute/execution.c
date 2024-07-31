/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:39:40 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/31 09:53:08 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void get_path(t_data *data, t_cmd *cmd)
{
    int i;
    char *path;
    char *temp;

    i = 0;
    if (!cmd->av)
        return ;
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

int check_access(t_cmd *temp)
{
    if (access(temp->av[0], X_OK) == 0)
        return 1;
    return (0);
}

void execute_cmd(t_data *data, int i)
{
    t_cmd   *temp;

    temp = data->cmds;
    while(i > 0)
    {
        temp = temp->next;
        i --;
    }
    get_path(data, temp);
    if (temp->path != NULL && temp->av)
    {
        if(execve(temp->path, temp->av, data->envp) != 0)
            perror("eitoimi\n");
    }
    else
    {
        if (!temp->av)
            printf("no command\n");
        if(check_access(temp) != 0)
        {
            if (execve(temp->av[0], temp->av, data->envp) == -1)
                perror("exe: ");
        }
        else
            printf("%s: command not found\n", temp->av[0]);
        data->exit_code = 127;
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
