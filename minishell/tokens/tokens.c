/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:01:56 by asalo             #+#    #+#             */
/*   Updated: 2024/07/12 14:49:04 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/tokens.h"

static char    *get_next(char *s)
{
    static char *temp;
    char        *tkn;

    if (!s)
        temp = s;
    while (temp && *temp && ft_strchr(" \n\t\r\v\f", *temp))
        temp++;
    if (!temp || !*temp)
        return (0);
    tkn = temp;
    temp = &temp[unquoted_char(temp, " \n\t\r\v\f", "\'\"")];/*Make this function*/
    if (*temp)
    {
        temp++;
        *temp = '\0';
    }
    return (tkn);
}

static t_token    *get_tkns(char *s)
{
    t_token *tokens;
    t_token *last;
    t_token *tkn;

    tkn = get_next(s);
    if (!tkn)
        return (0);
    tokens = new_token(ft_strdup(tkn));
    if (!tokens)
        return (0);
    last = tokens;
    while (1)
    {
        tkn = get_next(0);
        if (!tkn)
            break ;
        last = last->next;
        if (!last)
            return (tkn_free(tokens), 0);
    }
    return (tokens);
}

t_token *tokenizer(int *status, char *s)
{
    t_token *tokens;
    int     eval;

    tokens = get_tkns(s);
    free(s);
    if (!tokens || split_at_operators(tokens) == FAIL)
    {
        *status =eval;
        return (tkn_free(tokens), 0);
    }
    return (tokens);
}