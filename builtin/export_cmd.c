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
 * export without args --> show env list
 *  - env list pitaisi olla aakkosjarjestyksessa (ehka)
 * 
 * 
 */

void    add_list(t_tools *tools)
{
    int i;
    int j;
    char *temp;

    i = 0;
    j = 0;
    tools->new_envp = malloc((ft_arraylen(tools->envp) + 2) * sizeof(char));
    while(tools->envp[i] != NULL)
    {
        tools->new_envp[i] = tools->envp[i]; 
        i ++;
    }
    temp = ft_strdup(tools->split_rl[1]);
    tools->new_envp[i] = temp;
    tools->new_envp[i + 1] = NULL;
    tools->envp = tools->new_envp;
}

void    output_list(t_tools *tools)
{
	int i;
    
    i = 0;
    while(tools->envp[i] != NULL)
    {
        printf("declare -x ");
        printf("%s\n", tools->envp[i]);
        i ++;
    }
}

void	export_cmd(t_tools *tools)
{
    if (tools->split_rl[1] == NULL)
        output_list(tools);
    if (tools->split_rl[1])
        add_list(tools); 
}