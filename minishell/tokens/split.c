/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:42:53 by asalo             #+#    #+#             */
/*   Updated: 2024/07/12 13:59:41 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/tokens.h"

static  char    split_token(t_token *token, size_t start)
{
    t_token *new;
    size_t  len;

    len = ft_strlen(&token->content[start]);
    new = new_token(ft_substr(token->content, start, len));
    if (!new)
        return (FAIL);
    new->next = token->next;
    token->next = new;
    token->content[start] ='\0';
    return (SUCCESS);
}

static char checker(t_token *token)
{
    size_t  i;

    i = unquoted_char(token->content, "<>|", "\'\"");
    if (!token->content[i])
        return (SUCCESS);
    if(i)
        return (split_token(token, i));
    i += 1 + (ft_strchr("<>", token->content[i])
        && token->content[i] == token->content[i + 1]);
    if (!token->content[i])
        return (SUCCESS);
    return (split_token(token, i));
}

char    split_at_operators(t_token *tokens)
{
    while (tokens)
    {
        if (checker(tokens) == FAIL)
            return (FAIL);
        tokens = tokens->next;
    }
    return (SUCCESS);
}