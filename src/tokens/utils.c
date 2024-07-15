/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:55:15 by asalo             #+#    #+#             */
/*   Updated: 2024/07/14 14:56:50 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/tokens.h"

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = next;
	}
}

void  free_cmds(t_cmd *cmds)
{
    t_cmd   *tmp;
    size_t  i;

    while (cmds)
    {
        tmp = cmds->next;
        free(cmds->path);
        i = 0;
        while (cmds->av && cmds->av[i])
            free(cmds->av[i++]);
        free(cmds->av);
        free_tokens(cmds->io_redir);
        if (cmds->fd_in != STDIN_FILENO)
            close(cmds->fd_in);
        if (cmds->fd_out != STDOUT_FILENO)
            close(cmds->fd_out);
        free(cmds);
        cmds = tmp;
    }
}
