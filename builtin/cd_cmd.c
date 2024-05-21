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
 * cd without cmd and unsetted HOME works now. 
 * cd with path: somehow works -- need more test and error handling
 * cd with .. : somehow works -- need more test and error handling
 * cd with dir name : somehow works -- need more test and error handling
 * cd with invalid dir name : works -- need more testing
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
        if (ft_strncmp(tools->envp[i], str, ft_strlen(str)) == 0)
            temp_path = tools->envp[i];
        i ++;
    }
    if (!temp_path)
        printf("cd: HOME not set\n"); 
    else
        trim_path(tools, temp_path, str);
}

void trim_last(t_tools *tools)
{
    char *pwd;
    int i;
    int len;

    pwd = getcwd(NULL, 0);
    if (!pwd)
        perror("pwd");
    i = 0;
    len = ft_strlen(pwd);
    while (len > 1)
    {
        if (pwd[len] == '/')
            break ;
        len --;
    }
    tools->prev_path = malloc(len * sizeof(char));
    while(i < len)
    {
        tools->prev_path[i] = pwd[i];
        i ++;
    }
    tools->prev_path[i] = '\0';
    if (pwd)
        free(pwd);
}

void    cd_cmd(t_tools *tools)
{
    if (tools->split_rl[1] == NULL)
    {
        get_path(tools, "HOME=");
        if (chdir(tools->path) == -1)
            perror("cd");
    }
    else if (ft_strncmp(tools->split_rl[1], "..", 2) == 0)
    {
        trim_last(tools);
        if (chdir(tools->prev_path) == -1)
            perror("cd");
        free(tools->prev_path); 
    }
    else
    {
        if (chdir(tools->split_rl[1]) == -1)
            perror("cd");
    }
}
