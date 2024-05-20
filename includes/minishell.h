/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:11:52 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/07 14:11:54 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_tools
{
    char    *rl;
    char    **split_rl;
    char    *path;
    char    **paths;
    char    **envp;
    int     end; 

}   t_tools;

void run(char **envp);
void parse(t_tools *tools);

//builtins
void exit_cmd(t_tools *tools);
void cd_cmd(t_tools *tools);
void env_cmd(t_tools *tools);
void echo_cmd(t_tools *tools);
void pwd_cmd(t_tools *tools);

//utils.c
void free_array(char **arr);
void free_all(t_tools *tools);

#endif
