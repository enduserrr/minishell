/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:21:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/30 10:51:36 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

/**
 * @brief	Checks command count and sets command into token content.
 *			If it's a pipe, skips ahead.
*/
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

static void	alter_token(t_token **tokens)
{
	t_token	*temp;
	t_token	*tkn;
	t_token	*next;

	temp = NULL;
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
			if (temp)
				temp->next = next;
			else
				*tokens = next;
		}
		else
			temp = tkn;
		tkn = next;
	}
}

static void	set_redir(t_token *tokens, t_cmd *commands)
{
	t_token	*temp;
	t_token	*next;

	temp = NULL;
	while (tokens)
	{
		if (tokens->id != PIPE)
			commands->io_redir = tokens;
		while (tokens && tokens->id != PIPE)
		{
			temp = tokens;
			tokens = tokens->next;
		}
		if (!tokens)
			return ;
		commands = commands->next;
		if (temp)
			temp->next = NULL;
		next = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = next;
	}
}

t_cmd	*command_table(t_token *tokens)
{
	t_cmd	*commands;

	commands = alloc_cmd(tokens);
	if (!commands)
		return (set_err(MEM_ERR, "creating command table"), NULL);
	args_to_table(tokens, commands);
	alter_token(&tokens);
	set_redir(tokens, commands);
	return (commands);
}
