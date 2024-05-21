/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:37:04 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/20 22:37:15 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

/*
 * cd without cmd: somehow work -- need more test and error handling
 *      - segfault if already home
 * cd with path: somehow works -- need more test and error handling
 * 
 * cd with .. : somehow works -- need more test and error handling
 * 
 * cd with dir name : somehow works -- need more test and error handling
 * 
 * 
 * what happens after unsetting path? and what is supposed to happen.. 
 * 
 */
void    trim_path(t_tools *tools, char *temp_path, char *str)
{
    int i;
    int len; 

    i = 0;
    len = ft_strlen(str);
    while(i < len)
    {
        temp_path ++; 
        i ++;
    }
    tools->path = temp_path;
}

void    get_path(t_tools *tools, char *str)
{
    int i;
    char *temp_path;

    i = 0;
    while(tools->envp[i] != NULL)
    {
        if (ft_strncmp(tools->envp[i], str, 5) == 0)
            temp_path = tools->envp[i];
        i ++;
    }
    trim_path(tools, temp_path, str);
}

void trim_last(t_tools *tools, char *dir)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(dir);
    while (len > 1)
    {
        if (dir[len] == '/')
            break ;
        len --;
    }
    tools->prev_path = malloc(len * sizeof(char));
    while(i < len)
    {
        tools->prev_path[i] = dir[i];
        i ++;
    }
    tools->prev_path[i] = '\0'; 
}

void    cd_cmd(t_tools *tools)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    if (tools->split_rl[1] == NULL)
    {
        get_path(tools, "HOME=");
        chdir(tools->path);
    }
    else if (ft_strncmp(tools->split_rl[1], "..", 2) == 0)
    {
        trim_last(tools, pwd);
        chdir(tools->prev_path);
        free(tools->prev_path); 
    }
    else
        chdir(tools->split_rl[1]);
    free(pwd);
}
