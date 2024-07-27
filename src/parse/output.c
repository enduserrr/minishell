/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_results.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:34:46 by asalo             #+#    #+#             */
/*   Updated: 2024/07/23 12:40:55 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

static t_token *put_token(t_token *tokens, const char *title)
{
	if (title)
        printf("\e[1;33m%s\e[0m\n", title);
    if (!tokens)
        printf("No tokens\n");
    while (tokens)
    {
        if (tokens->id == WORD)
            printf("[WORD] ");
        else if (tokens->id == IN_FILE)
            printf("[IN_FILE] ");
        else if (tokens->id == OUT_FILE)
            printf("[OUT_FILE] ");
		else if (tokens->id == HEREDOC_EOF)
			printf("[HEREDOC_EOF] ");
		else if (tokens->id == OUT_A_FILE)
			printf("[OUT_A_FILE] ");
		else if (tokens->id == COMMAND)
			printf("[COMMAND] ");
		else if (tokens->id == OPERATOR)
			printf("[OPERATOR] ");
		else if (tokens->id == IN_REDIR)
			printf("[IN_RED] ");
		else if (tokens->id == OUT_REDIR)
			printf("[OUT_RED] ");
		else if (tokens->id == HEREDOC)
			printf("[HEREDOC] ");
		else if (tokens->id == OUT_A_REDIR)
			printf("[OUT_A_RED] ");
		else if (tokens->id == PIPE)
			printf("[PIPE] ");
		printf("[%s]\n", tokens->content);
		tokens = tokens->next;
	}
	return (tokens);
}

void	put_command(t_cmd *commands)
{
	size_t	i;

	printf("\e[7;37mCOMMANDS\e[0m\n");
	if (!commands)
		printf("no commands\n");
	while (commands)
	{
		printf("path:\t%s\n", commands->path);
		printf("args:\t");
		i = 0;
		while (commands->av && commands->av[i])
			printf("[%s]", commands->av[i++]);
		printf("\nredir:\t");
		put_token(commands->io_redir, 0);
		printf("fd_in:\t%d\nfd_out:\t%d\n", commands->fd_in, commands->fd_out);
		commands = commands->next;
		if (commands)
            printf("=========================>\n");
	}
}