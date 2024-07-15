/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:33:34 by asalo             #+#    #+#             */
/*   Updated: 2024/07/15 13:38:53 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/tokens.h"
/*Make: string_inserter() & asprintf() functions*/
static void	tilde_expand(char **s, size_t i)
{
	struct stat	stats;
	ssize_t		end;
	char		*path;

	if ((*s)[i] != '~')
		return ;
	if (getenv("HOME") && ((*s)[i + 1] == '\0' || (*s)[i + 1] == '/'))
		// string_inserter(s, getenv("HOME"), t, 1);
	else if (getenv("PWD") && (*s)[i + 1] == '+'
		&& ((*s)[i + 2] == '\0' || (*s)[i + 2] == '/'))
		// string_inserter(s, getenv("PWD"), t, 2);
	else if (getenv("OLDPWD") && (*s)[i + 1] == '-'
		&& ((*s)[i + 2] == '\0' || (*s)[i + 2] == '/'))
		// string_inserter(s, getenv("OLDPWD"), t, 2);
	else if ((*s)[i + 1])
	{
		end = set_char(*s + i, '\0', ft_strchr_index(*s + i, '/'));
		asprintf(&path, "/Users/%s", *s + i + 1);/*alloc string printf*/
		end = set_char(*s + i, '/', end);
		if (path && !stat(path, &stats) && S_ISDIR(stats.st_mode))
			// string_inserter(s, path, i, end);
		free(path);
	}
}

static void	assignement_tilde(char **s)
{
	size_t	i;

	i = 0;
	if (ft_isalpha((*s)[i]))
		while (ft_isalnum((*s)[i]) || (*s)[i] == '_')
			i++;
	if (i && (*s)[i] == '=')
		tilde_expand(s, i + 1);
}

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

char	expand_tkns(int status, t_token **tokens)
{
	t_token	*tkn;
	char		return_val;

	tkn = *tokens;
	while (tkn)
	{
		return_val = RETURN_SUCCESS;
		if (tkn->id & WORD && tkn->id != HEREDOC_EOF)
		{
			tilde_expand(&tkn->content, 0);
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