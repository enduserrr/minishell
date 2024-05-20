/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:38:10 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/20 22:38:13 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

/*
 * Command exit frees everything and closes program
 */

void exit_cmd(t_tools *tools)
{
    free_all(tools);
    printf("exit\n");
    exit(EXIT_SUCCESS);
}
