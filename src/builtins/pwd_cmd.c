/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:45:34 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/02 11:02:27 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	pwd_cmd(t_data *data)
{
	char	*pwd;

	data->exit_code->state = 0;
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
