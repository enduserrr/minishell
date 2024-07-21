/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:18:25 by asalo             #+#    #+#             */
/*   Updated: 2024/07/21 11:38:45 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

static  void    check_operators(t_token *tokens)
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

static char *check_redirs(t_token *tokens)
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

static char *check_syntax(t_token *tokens)
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

void    eval_commands(t_token *tokens)
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

int check_tokens(t_token *tokens)
{
    char    *context;

    check_operators(tokens);
    context = check_redirs(tokens);
    if (context)
        return (parsing_err(TKN_SYNTAX_ERR, context));
    eval_commands(tokens);
    context = check_syntax(tokens);
    if (context)
        return (parsing_err(TKN_SYNTAX_ERR, context));
    return (RETURN_SUCCESS);
}