/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:18:25 by asalo             #+#    #+#             */
/*   Updated: 2024/08/08 18:06:12 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

/**
 * @brief   Assigns the correct operator id.
 */
static void	check_operators(t_token *tokens)
{
	while (tokens)
	{
		if (!ft_strcmp(tokens->content, "<"))
			tokens->id = IN_REDIR;
		else if (!ft_strcmp(tokens->content, ">"))
			tokens->id = OUT_REDIR;
		else if (!ft_strcmp(tokens->content, "<<"))
			tokens->id = HEREDOC;
		else if (!ft_strcmp(tokens->content, ">>"))
			tokens->id = OUT_A_REDIR;
		else if (!ft_strcmp(tokens->content, "|"))
			tokens->id = PIPE;
		tokens = tokens->next;
	}
}

/**
 * @brief   Checks for redirections and the following
 *          file tokens and updates their id's.
 */
static char	*check_redirs(t_token *tokens)
{
	while (tokens && tokens->next)
	{
		if (tokens->id & OPERATOR && tokens->id != PIPE
			&& tokens->next->id & OPERATOR)
			return (tokens->next->content);
		if (tokens->id == IN_REDIR)
			tokens->next->id = IN_FILE;
		else if (tokens->id == OUT_REDIR)
			tokens->next->id = OUT_FILE;
		else if (tokens->id == OUT_A_REDIR)
			tokens->next->id = OUT_A_FILE;
		else if (tokens->id == HEREDOC)
			tokens->next->id = HEREDOC_EOF;
		tokens = tokens->next;
	}
	return (NULL);
}

/**
 * @brief   Ensures correct syntax
 *          (not pipe at start, end in an operator or unmatched quotes)
 */
static char	*check_syntax(t_token *tokens)
{
	size_t	i;
	char	quote;

	if (tokens->id == PIPE)
		return (tokens->content);
	while (tokens->next)
		tokens = tokens->next;
	if (tokens->id & OPERATOR)
		return ("newline");
	quote = 0;
	i = 0;
	while (tokens->content[i])
	{
		if (!quote && ft_strchr("\'\"", tokens->content[i]))
			quote = tokens->content[i];
		else if (tokens->content[i] == quote)
			quote = 0;
		i++;
	}
	if (quote)
		return (tokens->content);
	return (NULL);
}

void	check_commands(t_token *tokens)
{
	while (tokens)
	{
		while (tokens && tokens->id != WORD && tokens->id != COMMAND)
			tokens = tokens->next;
		if (!tokens)
			return ;
		tokens->id = COMMAND;
		while (tokens && tokens->id != PIPE)
			tokens = tokens->next;
	}
}

int	check_tokens(t_token *tokens, t_exit *state)
{
	char	*context;

	check_operators(tokens);
	context = check_redirs(tokens);
	if (context)
		return (set_err(1, context, state));
	check_commands(tokens);
	context = check_syntax(tokens);
	if (context)
		return (set_err(1, context, state));
	return (0);
}
