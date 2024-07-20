/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:21:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/20 19:20:54 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"


static void	args_to_table(t_token *tokens, t_cmd *commands)
{
	size_t	av_count;

	av_count = 0;
	while (tokens)
	{
		if (tokens->id == COMMAND || tokens->id == WORD)
			commands->av[av_count++] = tokens->content;
		else if (tokens->id == PIPE)
		{
			commands = commands->next;
			av_count = 0;
		}
		tokens = tokens->next;
	}
}

static void	alter_tkn(t_token **tokens)
{
	t_token	*prev;
	t_token	*tkn;
	t_token	*next;

	prev = NULL;
	tkn = *tokens;
	while (tkn)
	{
		next = tkn->next;
		if ((tkn->id & OPERATOR) && tkn->id != PIPE)
			free(tkn->content);
		if (((tkn->id & OPERATOR) && tkn->id != PIPE)
			|| tkn->id == COMMAND || tkn->id == WORD)
		{
			free(tkn);
			if (prev)
				prev->next = next;
			else
				*tokens = next;
		}
		else
			prev = tkn;
		tkn = next;
	}
}

static void	redir_to_table(t_token *tokens, t_cmd *commands)
{
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	while (tokens)
	{
		if (tokens->id != PIPE)
			commands->io_redir = tokens;
		while (tokens && tokens->id != PIPE)
		{
			prev = tokens;
			tokens = tokens->next;
		}
		if (!tokens)
			return ;
		commands = commands->next;
		if (prev)
			prev->next = NULL;
		next = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = next;
	}
}

t_cmd	*create_cmd_table(t_token *tokens)
{
	t_cmd	*commands;

	commands = alloc_cmd(tokens);
	if (!commands)
		return (parsing_err(MEM_ERR, "creating command table"), NULL);
	args_to_table(tokens, commands);
	alter_tkn(&tokens);
	redir_to_table(tokens, commands);
	return (commands);
}
