 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EDIHEADER.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:31:39 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/21 15:31:45 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//////DO PROPER HEADER AT SCHOOL/////

#include "../includes/minishell.h"

/*
//  For testing (if need to see whats in history)
//------------------------------------------------
void output_history(t_tools *tools)
{
    t_hist *temp;

    temp = tools->history;
    printf("----history----\n");
    while(temp)
    {
        printf("%s\n", temp->cmd);
        temp = temp->next;
    }
} 
// --------------------------------------------------
*/


void free_history(t_tools *tools)
{
    t_hist *current;
    t_hist *temp;

    current = tools->history;
    while(current != NULL)
    {
        temp = current->next;
        free(current->cmd);
        free(current);
        current = temp;
    }
}

void add_to_history(t_tools *tools)
{
    t_hist  *new;
    t_hist  *temp;

    temp = NULL;
    temp = tools->history;
    if (tools->history->cmd == NULL && tools->history->next == NULL)
        tools->history->cmd = ft_strdup(tools->rl);
    else
    {
        new = malloc(sizeof(t_hist));
        if (!new)
            perror("malloc");
        new->cmd = ft_strdup(tools->rl);
        new->next = NULL;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }    
    //output_history(tools); //for test only
}

void create_history(t_tools *tools)
{
    t_hist  *history;

    history = malloc(sizeof(t_hist));
    if(!history)
        perror("history");
    history->cmd = NULL;
    history->next = NULL;
    tools->history = history;
}
