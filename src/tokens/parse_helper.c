/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:19:50 by asalo             #+#    #+#             */
/*   Updated: 2024/07/14 14:54:33 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/tokens.h"

/**
 * @brief   ssize_t range from -1 to SIZE_MAX
 *          Like size_t plus range for return failure.
*/
ssize_t set_char(char *s, char c, ssize_t i)
{
    if (c == '/' && i < 0)
		return (ft_strlen(s));
	if (!s || i < 0 || i > (ssize_t)ft_strlen(s))
		return (-1);
	s[i] = c;
	return (i);
}

/**
 * @brief "\e[1;33m" => escape (yellow text)
 *          Non printing escape sequence with color.
 *          ANSI escape sequences & printf escape sequenes.
*/

void	put_cmd(t_cmd *cmds)
{
	size_t	i;

	printf("\e[1;33mCOMMANDS\e[0m\n");
	if (!cmds)
		printf("No commands\n");
	while (cmds)
	{
		printf("PATH: %s\n", cmds->path);
		printf("ARGS%d:", !!cmds->av);
		i = 0;
		while (cmds->av && cmds->av[i])
			printf("[%s]", cmds->av[i++]);
		printf("\nREDIRECTIONS:\n");
		put_tkn(cmds->io_redir, 0);
		printf("fd_in: %d\nfd_out: %d\n", cmds->fd_in, cmds->fd_out);
		cmds = cmds->next;
		if (cmds)
			printf("\e[0;33m↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓\e[0m\n");
	}
}