/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:20:32 by asalo             #+#    #+#             */
/*   Updated: 2024/07/21 12:54:21 by asalo            ###   ########.fr       */
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

static ssize_t set_char(char *s, char c, ssize_t i)
{
    if (c == '/' && i < 0)
		return (ft_strlen(s));
	if (!s || i < 0 || i > (ssize_t)ft_strlen(s))
		return (-1);
	s[i] = c;
	return (i);
}

/**
 * @brief	Expands tilde ('~') set dir based on what it's followed by.
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
		path = create_user_path(*s + i + 1);
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
 * @brief	Iterates through the token list and
 *			expands tildes (~) or env vars.
 */
char	ft_expand(int status, t_token **tokens)
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
			return_val = expand_env(&tkn->content, status, tkn->id);
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
