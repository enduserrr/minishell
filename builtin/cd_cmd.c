/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:37:04 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/20 22:37:15 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
/*
void run_cd(t_tools *tools)
{
    
    execve(tools->polku, "..", tools->envp);


}
*/

/*
 * Does not do anything yet... 
 */

void cd_cmd(t_tools *tools)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    printf("pwd: %s", pwd);

    if (ft_strncmp(tools->split_rl[1], "..", 2) == 0)
    {
        printf(" do .. \n");
    }
    free(pwd);
}
