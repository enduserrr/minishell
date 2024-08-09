/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:34:46 by asalo             #+#    #+#             */
/*   Updated: 2024/08/09 12:52:01 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

/*static t_token	*put_token(t_token *tokens, const char *title)
{
	if (title)
		printf("\e[1;90m%s\e[0m\n", title);
	if (!tokens)
		printf("\33[90mNo tokens\e[0m\n");
	while (tokens)
	{
		if (tokens->id == WORD)
			printf("\33[90m[WORD]\e[0m ");
		else if (tokens->id == IN_FILE)
			printf("\33[90m[IN_FILE]\e[0m ");
		else if (tokens->id == OUT_FILE)
			printf("\33[90m[OUT_FILE]\e[0m ");
		else if (tokens->id == HEREDOC_EOF)
			printf("\33[90m[HEREDOC_EOF]\e[0m ");
		else if (tokens->id == OUT_A_FILE)
			printf("\33[90m[OUT_A_FILE]\e[0m ");
		else if (tokens->id == COMMAND)
			printf("\33[90m[COMMAND]\e[0m ");
		else if (tokens->id == OPERATOR)
			printf("\33[90m[OPERATOR]\e[0m ");
		else if (tokens->id == IN_REDIR)
			printf("\33[90m[IN_RED]\e[0m ");
		else if (tokens->id == OUT_REDIR)
			printf("\33[90m[OUT_RED]\e[0m ");
		else if (tokens->id == HEREDOC)
			printf("\33[90m[HEREDOC]\e[0m ");
		else if (tokens->id == OUT_A_REDIR)
			printf("\33[90m[OUT_A_RED]\e[0m ");
		else if (tokens->id == PIPE)
			printf("\33[90m[PIPE]\e[0m ");
		printf("\33[90m[%s]\e[0m\n", tokens->content);
		tokens = tokens->next;
	}
	return (tokens);
}*/

/*void	put_command(t_cmd *commands)
{
	size_t	i;

	printf("\e[7;90mCOMMANDS\e[0m\n");
	if (!commands)
		printf("\33[90mno commands\e[0m\n");
	while (commands)
	{
		printf("\33[90mpath:\t%s\e[0m\n", commands->path);
		printf("\33[90margs:\t");
		i = 0;
		while (commands->av && commands->av[i])
			printf("\33[90m[%s]\e[0m", commands->av[i++]);
		printf("\33[90m\nredir:\e[0m\t");
		put_token(commands->io_redir, 0);
		printf("\33[90mfd_in:\t%d\nfd_out:\t%d\e[0m\n", commands->fd_in,
			commands->fd_out);
		commands = commands->next;
		if (commands)
			printf("\33[90m=========================>\e[0m\n");
	}
}*/
