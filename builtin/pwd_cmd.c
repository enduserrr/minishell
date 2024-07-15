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

void	pwd_cmd(t_tools *tools)
{
	char	*pwd;

	tools->exit_code = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror("pwd: ");
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}

/*
 * DELETE THIS
 *
 * outputs curret pwd
 *
 * getcwd(NULL, 0) works, but don't know do i we need to do changes
 *
 */