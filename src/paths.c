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

#include "../incs/minishell.h"

void delete_paths(t_data *data)
{
    free_array(data->paths);
    data->paths = NULL;

}

void create_paths(t_data *data)
{
    t_env   *temp;
    
    temp = data->env_list;
    while(temp->next != NULL)
    {
        if (ft_strncmp(temp->key, "PATH", 4) == 0)
        {
            data->paths = ft_split(temp->value, ':');
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
 *      usage:
 *          - creates path array in start of run() function 
 * 
 *  - delete_paths():
 *      - deletes array that stores paths
 * 
 *      usage: 
 *          - if command is "unset PATH" 
 *          - 
 *
 *
 */
