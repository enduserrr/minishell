/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:31:04 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/21 15:31:07 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Export shows envlist like export does: 
 *  - declare -x USER="eleppala"
 *  
 * Puutteet: 
 *  - export lista aakkosjarjestykseen
 *  - jonkunlainen check, jos variable on jo olemassa 
 *  - uuden variablen lisaaminen aakkosjarjestettyyn listaan
 */

void    add_new(t_tools *tools, char *str)
{
    t_env   *temp;
    t_env   *new;
    char    **temp_arr;

    temp_arr = ft_split(str, '=');
    new = malloc(sizeof(t_env));
    new->key = ft_strdup(temp_arr[0]);
    new->value = ft_strdup(temp_arr[1]);
    new->next = NULL;
    free_array(temp_arr);
    temp = tools->env_list;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new;
}

/*
 * outputs envlist like export does, 
 *  - later make them in alphabetical order, good for now
 */

void    output_export(t_env *env)
{
    t_env *ptr;

    ptr = env;
    while(ptr != NULL)
    {
        printf("declare -x %s=\"%s\" \n", ptr->key, ptr->value);
        ptr = ptr->next;
    }
}

void	export_cmd(t_tools *tools)
{
    if (tools->split_rl[1] == NULL)
        output_export(tools->env_list);
    if (tools->split_rl[1])
        add_new(tools, tools->split_rl[1]);
}