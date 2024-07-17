/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkns.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:01:56 by asalo             #+#    #+#             */
/*   Updated: 2024/07/17 13:00:59 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/tokens.h"

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = next;
	}
}

static char    *get_next(char *s)
{
    static char *temp;
    char        *tkn;
    size_t      i;

    if (!s)
        temp = s;
    while (temp && *temp && ft_strchr(" \n\t\r\v\f", *temp))
        temp++;
    if (!temp || !*temp)
        return (0);
    tkn = temp;
    i = unquoted_char(temp, " \n\t\r\v\f", "\'\"");
    temp = &temp[i];
    if (temp[i])
        temp[++i] = '\0';
    return (tkn);
}

t_token	*new_token(char *content)
{
	t_token	*new;

	if (!content)
		return (parsing_err(MEM_ERR, "creating token content"), NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (parsing_err(MEM_ERR, "creating token"), free(content), NULL);
	new->id = WORD;
	new->content = content;
	new->next = NULL;
	return (new);
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
        tkn = get_next(NULL);
        if (!tkn)
            break ;
        last->next = new_token(ft_strdup(tkn));
        last = last->next;
        if (!last)
            return (free_tokens(tokens), 0);
    }
    return (tokens);
}

t_token *tokenizer(int *status, char *s)
{
    t_token *tokens;
    int     eval;

    tokens = get_tkns(s);
    free(s);
    if (!tokens || split_at_operators(tokens) == RETURN_FAILURE)
    {
        status = MEM_ERR;
        return (free_tokens(tokens), 0);
    }
    eval = check_tokens(tokens);
    if (eval != RETURN_SUCCESS)
    {
        status = eval;
        return (free_tokens(tokens), 0);
    }
    return (tokens);
}