/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:45:34 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/20 22:46:57 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Shows current working directory 
 * 
 * -- dont know yet how to error is supposed to handle properly -- 
 */

void pwd_cmd(t_tools *tools)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    if (!pwd)
        free_all(tools); 
    printf("%s\n", pwd);
    free(pwd);
}
