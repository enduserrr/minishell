/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:45:34 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/22 14:21:48 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief	 * Shows current working directory
 *			tools argumenttina, vain varmuuden vuoksi. otetaan pois jos ei tule kayttoa.
 *
 *			-- dont know yet how this getcwd error is supposed to handle properly --
*/
void	pwd_cmd(t_tools *tools)
{
	char	*pwd;

	(void)tools->path;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror("pwd: ");
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}
