/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:01:44 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/22 14:01:47 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * for freeing env_list from t_tools->env_list 
 */


void free_env(t_tools *tools)
{
    t_env   *current;
    t_env   *temp; 

    current = tools->env_list;
    while(current != NULL)
    {   
        temp = current->next;
        free(current->var);
        free(current);
        current = temp; 
    }

}

/*
 * add element end of the list 
 * might be usefull to add more data than just one str dont know yet... 
 *  -  example key value pair:
 *  -  temp->key = HOME= 
 *  -  temp->value = Users/eleppala
 */

void    add(t_env *env, t_tools *tools, int i)
{
    t_env   *temp;
    t_env  *temp2;

    temp2 = env;
    temp = malloc(sizeof(t_env));
    temp->var = ft_strdup(tools->envp[i]);
    temp->next = NULL;
    while(temp2->next != NULL)
        temp2 = temp2->next;
    temp2->next = temp; 
}

/*
 * for now print_env is only for testing.. 
 */

void    print_env(t_env *env)
{
    t_env *ptr;
    int i;

    i = 0;
    ptr = env;
    while(ptr != NULL)
    {
        printf("%s\n", ptr->var);
        ptr = ptr->next;
        i ++;
    }

}

/*
 * Create first element of t_env *env, loop trough env list 
 * add environment variables one by one to a linked list 
 */

void   create_env_list(t_tools *tools)
{
    t_env *env;
    int i;

    i = 1;
    env = malloc(sizeof(t_env));
    env->var = ft_strdup(tools->envp[0]);
    env->next = NULL; 
    while(i < ft_arraylen(tools->envp))
    {
        add(env, tools, i);
        i ++;
    }
    tools->env_list = env;
}