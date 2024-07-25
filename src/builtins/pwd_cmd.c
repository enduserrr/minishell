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

#include "../../incs/minishell.h"

void	pwd_cmd(t_data *data)
{
	char	*pwd;

	data->exit_code = 0;
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
 * - outputs current pwd
 * - should work with | or other args
 * - "pwd" "randomshit" --> should output pwd
 * - "pwd" | wc -l --> lines of pwd 
 * - "pwd"
 *
 */