/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:45:34 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/15 09:05:23 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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