/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:48:36 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/07 18:48:38 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void free_array(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void free_all(t_tools *tools)
{
    //if (tools->path != 0)  // ei viela mitaan mika tarvitsee vapautusta
        //free(tools->path);
    if (tools->split_rl != 0)
        free_array(tools->split_rl);
}