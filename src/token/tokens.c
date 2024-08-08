/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:01:56 by asalo             #+#    #+#             */
/*   Updated: 2024/08/08 11:24:05 by asalo            ###   ########.fr       */
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
 * @brief   Inits a new token (allocs mem, assigns id and next ptr.
 */
t_token	*new_token(char *content, t_exit *state)
{
	t_token	*new;

	if (!content)
		return (set_err(MEM_ERR, "creating token content", state), NULL);
    // new = ft_calloc(1, sizeof(t_token));
    new = malloc(sizeof(t_token));
	if (!new)
		return (set_err(MEM_ERR, "creating token", state), free(content), NULL);
	new->id = WORD;
	new->content = content;
	new->next = NULL;
	return (new);
}

/**
 * @brief   Next token from str (readline). Skips white spaces and
 *          deals with quoted tokens. Returns the next token or a NULL.
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
 * @brief   Init linked list for tokens. Calls get_next() to init the nbr of
 *          nodes required. Returns ptr to top node
 */
static t_token    *get_tokens(char *s, t_exit *state)
{
    t_token *tokens;
    t_token *last;
    char    *tkn;

    tkn = get_next(s);
    if (!tkn)
        return (NULL);
    tokens = new_token(ft_strdup(tkn), state);
    if (!tokens)
        return (NULL);
    last = tokens;
    while (1)
    {
        tkn = get_next(NULL);
        if (!tkn)
            break ;
        last->next = new_token(ft_strdup(tkn), state);
        last = last->next;
    }
    return (tokens);
}

t_token *ft_token(t_exit *state, char *s)
{
    t_token *tokens;
    int     eval;

    tokens = get_tokens(s, state);
    free(s);
    if (!tokens || split_at_operators(tokens, state) == 1)
    {
        if (!tokens)
            return (NULL);
        state->state = MEM_ERR;
        return (free_tokens(tokens), NULL);
    }
    eval = check_tokens(tokens, state);
    if (eval != 0)
    {
        state->state = eval;
        return (free_tokens(tokens), NULL);
    }
    return (tokens);
}
