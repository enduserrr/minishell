/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:52:09 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/15 10:52:14 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void create_paths(t_tools *tools)
{
    t_env   *temp;
    
    temp = tools->env_list;
    while(temp->next != NULL)
    {
        if (ft_strncmp(temp->key, "PATH", 4) == 0)
        {
            tools->paths = ft_split(temp->value, ':');
            break ;
        }
        temp = temp->next;
    }
}


/*
 *  DELETE THIS:
 *
 *  - create_paths(): 
 *      - splits PATH from env_list
 *      - splitted path list is needed for executing commands
 *      - array is stored to tools struct: tools->paths
 *  
 *  - check_access():
 *      - checks if command has valid path in path_list
 *      - 
 *
 *
 *
 */
