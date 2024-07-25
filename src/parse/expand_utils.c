/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:33:34 by asalo             #+#    #+#             */
/*   Updated: 2024/07/23 11:32:27 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

/**
 * @brief	Makes a filepath for the given username.
 */
static char *create_user_path(const char *username)
{
    const char	*prefix;
    size_t		len;
    char		*path;

	if (!username)
		return (NULL);
	prefix = "/Users/";
	len = ft_strlen(username) + ft_strlen(prefix);
	path = ft_calloc(len + 1, sizeof(char));
    if (!path)
        return (NULL);
    ft_memcpy(path, prefix, ft_strlen(prefix));
    ft_memcpy(&path[ft_strlen(prefix)], username, ft_strlen(username));
    path[len] = '\0';
    return (path);
}

/**
 * @brief	Expands tilde ('~') in a str (holding corresponding dir).
 *			Checks for commands or username followed by tilde
 *			to add correct env var or to create user home dir path.
 */
static void	tilde_expander(char **s, size_t i)
{
	struct stat	stats;
	ssize_t		end;
	char		*path;

	if ((*s)[i] != '~')
		return ;
	if (getenv("HOME") && ((*s)[i + 1] == '\0' || (*s)[i + 1] == '/'))
		ft_strinsrt(s, getenv("HOME"), i, 1);
	else if (getenv("PWD") && (*s)[i + 1] == '+'
		&& ((*s)[i + 2] == '\0' || (*s)[i + 2] == '/'))
		ft_strinsrt(s, getenv("PWD"), i, 2);
	else if (getenv("OLDPWD") && (*s)[i + 1] == '-'
		&& ((*s)[i + 2] == '\0' || (*s)[i + 2] == '/'))
		ft_strinsrt(s, getenv("OLDPWD"), i, 2);
	else if ((*s)[i + 1])
	{
		end = set_char(*s + i, '\0', ft_strichr(*s + i, '/'));
		path = create_user_path(*s + i + 1);/*CHECK*/
		end = set_char(*s + i, '/', end);
		if (path && !stat(path, &stats) && S_ISDIR(stats.st_mode))
			ft_strinsrt(s, path, i, end);
		free(path);
	}
}

/**
 * @brief	Checks if a str has an assignment (VAR=~).
 *			If yes, calls tilde_expander to replace it with correct path.
 */
static void	assignement_tilde(char **s)
{
	size_t	i;

	i = 0;
	if (ft_isalpha((*s)[i]))
		while (ft_isalnum((*s)[i]) || (*s)[i] == '_')
			i++;
	if (i && (*s)[i] == '=')
		tilde_expander(s, i + 1);
}

/**
 * @brief	Removes specified token from t_token linked list
 *			and removes the spaces that was allocated to it.
 */
static t_token	*rm_token(t_token **top, t_token *remove)
{
	t_token	*current;
	t_token	*prev;

	current = *top;
	if (current == remove)
	{
		*top = current->next;
		free(current->content);
		free(current);
		return (*top);
	}
	while (current && current != remove)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return (NULL);
	prev->next = current->next;
	free(current->content);
	free(current);
	return (prev->next);
}

/**
 * @brief	Iterates through the token list and
 *			expands any tildes (~) or env var references.
 */
char	expand_tokens(int status, t_token **tokens)
{
	t_token	*tkn;
	char	return_val;

	tkn = *tokens;
	while (tkn)
	{
		return_val = RETURN_SUCCESS;
		if (tkn->id & WORD && tkn->id != HEREDOC_EOF)
		{
			tilde_expander(&tkn->content, 0);
			assignement_tilde(&tkn->content);
			return_val = ft_expand(&tkn->content, status, tkn->id);
			if (return_val == RETURN_FAILURE)
				return (RETURN_FAILURE);
			else if (return_val == RMV)
				tkn = rm_token(tokens, tkn);
		}
		if (return_val == RETURN_SUCCESS)
			tkn = tkn->next;
	}
	return (RETURN_SUCCESS);
}