/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:42:53 by asalo             #+#    #+#             */
/*   Updated: 2024/07/17 13:04:25 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/tokens.h"

size_t  unquoted_char(char *s, const char *chars, const char *quotes)
{
    size_t  i;
    char    quote;

    i = 0;
    quote = 0;
    while (s[i])
    {
        if (!quote && ft_strchr(chars, s[i]))
            break ;
        if (!quote && ft_strchr(quotes, s[i]))
            break ;
        else if (s[i] == quote)
            quote = 0;
        i++; 
    }
    return (i);
}

static  char    split_token(t_token *token, size_t start)
{
    t_token *new;
    size_t  len;

    len = ft_strlen(&token->content[start]);
    new = new_token(ft_substr(token->content, start, len));
    if (!new)
        return (RETURN_FAILURE);
    new->next = token->next;
    token->next = new;
    token->content[start] ='\0';
    return (RETURN_SUCCESS);
}

static char split_checker(t_token *token)
{
    size_t  i;

    i = unquoted_char(token->content, "<>|", "\'\"");
    if (!token->content[i])
        return (RETURN_SUCCESS);
    if(i)
        return (split_token(token, i));
    i += 1 + (ft_strchr("<>", token->content[i])
        && token->content[i] == token->content[i + 1]);
    if (!token->content[i])
        return (RETURN_SUCCESS);
    return (split_token(token, i));
}

char    split_at_operators(t_token *tokens)
{
    while (tokens)
    {
        if (split_checker(tokens) == RETURN_FAILURE)
            return (RETURN_FAILURE);
        tokens = tokens->next;
    }
    return (RETURN_SUCCESS);
}

t_token *put_tkn(t_token *tokens, const char *title)
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