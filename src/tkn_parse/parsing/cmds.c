/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:21:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/15 12:33:04 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/tokens.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:25:00 by asalo             #+#    #+#             */
/*   Updated: 2024/07/15 12:26:57 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/tokens.h"


static void	args_to_table(t_token *tokens, t_cmd *cmd)
{
	size_t	av_count;

	av_count = 0;
	while (tokens)
	{
		if (tokens->id == COMMAND || tokens->id == WORD)
			cmd->av[av_count++] = tokens->content;
		else if (tokens->id == PIPE)
		{
			cmd = cmd->next;
			av_count = 0;
		}
		tokens = tokens->next;
	}
}

static void	alter_tkn(t_token **tokens)
{
	t_token	*prev;
	t_token	*tok;
	t_token	*next;

	prev = NULL;
	tok = *tokens;
	while (tok)
	{
		next = tok->next;
		if ((tok->id & OPERATOR) && tok->id != PIPE)
			free(tok->content);
		if (((tok->id & OPERATOR) && tok->id != PIPE)
			|| tok->id == COMMAND || tok->id == WORD)
		{
			free(tok);
			if (prev)
				prev->next = next;
			else
				*tokens = next;
		}
		else
			prev = tok;
		tok = next;
	}
}

static void	redir_to_table(t_token *tokens, t_cmd *command)
{
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	while (tokens)
	{
		if (tokens->id != PIPE)
			command->io_redir = tokens;
		while (tokens && tokens->id != PIPE)
		{
			prev = tokens;
			tokens = tokens->next;
		}
		if (!tokens)
			return ;
		command = command->next;
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
	t_cmd	*cmds;

	cmds = alloc_cmd(tokens);
	if (!cmds)
		return (handle_perror(MEM_ERR, "creating command table"), NULL);
	args_to_table(tokens, cmds);
	alter_tkn(&tokens);
	redir_to_table(tokens, cmds);
	return (cmds);
}
