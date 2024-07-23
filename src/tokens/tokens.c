/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:01:56 by asalo             #+#    #+#             */
/*   Updated: 2024/07/23 12:04:27 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

/**
 * @brief   Free the tokens (t_token struct).
 */
void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
        if (tokens->content)
        {
		    free(tokens->content);
		    tokens->content = NULL;
        }
        free(tokens->content);
        free(tokens);
		tokens = next;
	}
}

/**
 * @brief   Creates a new token with the given content.
 *          Allocs memory for the token, assigns it's id and
 *          sets next node ptr.
 */
t_token	*new_token(char *content)
{
	t_token	*new;

	if (!content)
		return (set_err(MEM_ERR, "creating token content"), NULL);
    new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (set_err(MEM_ERR, "creating token"), free(content), NULL);
	new->id = WORD;
	new->content = content;
	new->next = NULL;
	return (new);
}

/**
 * @brief   Gets the next token from rl string.
 *          Static var to keep track of it's position on the str
 *          between calls. Skips white spaces and deals with quoted
 *          tokens. Returns the next token or a NULL.
 */
static char    *get_next(char *s)
{
    static char *temp;
    char        *tkn;

    if (s)
        temp = s;
    while (temp && *temp && ft_strchr(" \n\t\r\v\f", *temp))
        temp++;
    if (!temp || !*temp)
        return (NULL);
    tkn = temp;
    temp = &temp[unquoted_char(temp, " \n\t\r\v\f", "\'\"")];
    if (*temp)
        *temp++ = '\0';
    return (tkn);
}

/**
 * @brief   Generate linked list of tokens from the given str (rl).
 *          Repeatedly calls get_next to create as many nodes as there's
 *          tokens to be created. Return ptr to top node or NULL if no more
 *          tokens available.
 */
static t_token    *get_tokens(char *s)
{
    t_token *tokens;
    t_token *last;
    char    *tkn;

    tkn = get_next(s);
    if (!tkn)
        return (NULL);
    tokens = new_token(ft_strdup(tkn));
    if (!tokens)
        return (NULL);
    last = tokens;
    while (1)
    {
        tkn = get_next(NULL);
        if (!tkn)
            break ;
        last->next = new_token(ft_strdup(tkn));
        last = last->next;
        if (!last)
            return (free_tokens(tokens), NULL);
    }
    return (tokens);
}

t_token *ft_tokens(int *status, char *s)
{
    t_token *tokens;
    int     eval;

    tokens = get_tokens(s);
    free(s);
    if (!tokens || split_at_operators(tokens) == RETURN_FAILURE)
    {
        *status = MEM_ERR;
        return (free_tokens(tokens), NULL);
    }
    eval = check_tokens(tokens);
    if (eval != RETURN_SUCCESS)
    {
        *status = eval;
        return (free_tokens(tokens), NULL);
    }
    return (tokens);
}