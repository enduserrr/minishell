/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:42:53 by asalo             #+#    #+#             */
/*   Updated: 2024/08/02 11:29:07 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

/**
 * @brief   Finds the unquoted char from s and ignores quoted chars
 *          specified by 'quotes'.
 */
size_t	unquoted_char(char *s, const char *chars, const char *quotes)
{
	size_t	i;
	char	reference;

	i = 0;
	reference = 0;
	while (s[i])
	{
		if (!reference && ft_strchr(chars, s[i]))
			break ;
		if (!reference && ft_strchr(quotes, s[i]))
			reference = s[i];
		else if (s[i] == reference)
			reference = 0;
		i++;
	}
	return (i);
}

/**
 * @brief   Split token's content at the specified point into two.
 *          Creates new token from the second one and adds it to list.
 */
static char	split_tokens(t_token *token, size_t start, t_exit *state)
{
	t_token	*new;
	size_t	len;

	len = ft_strlen(&token->content[start]);
	new = new_token(ft_substr(token->content, start, len), state);
	if (!new)
		return (1);
	new->next = token->next;
	token->next = new;
	token->content[start] = '\0';
	return (0);
}

/**
 * @brief   Check's if token contains unquoted character (<>|)
 *          and splits if so. Handle's doubles (>>).
 */
static char	split_checker(t_token *token, t_exit *state)
{
	size_t	i;

	i = unquoted_char(token->content, "<>|", "\'\"");
	if (!token->content[i])
		return (0);
	if (i)
		return (split_tokens(token, i, state));
	i += 1 + (ft_strchr("<>", token->content[i])
			&& token->content[i] == token->content[i + 1]);
	if (!token->content[i])
		return (0);
	return (split_tokens(token, i, state));
}

/**
 * @brief   Goes through token list with split_checker()
 *          to find tokens with operator chars needing to be split.
 */
char	split_at_operators(t_token *tokens, t_exit *state)
{
	while (tokens)
	{
		if (split_checker(tokens, state) == 1)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
