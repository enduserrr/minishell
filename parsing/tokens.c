/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:32:27 by asalo             #+#    #+#             */
/*   Updated: 2024/06/04 08:19:54 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	arg_type(t_tkn *token, int sep)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && sep == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && sep == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && sep == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0 && sep == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && sep == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

void	handle_args(t_shell *shell)
{
	t_tkn	*token;
	t_tkn	*prev;

	token = shell->start;
	while (token)
	{
		prev = prev_sep(token, FALSE);
		if (is_type(token, ARG) && is_types(prev, "TAI"))
		{
			while (is_last_valid_arg(prev) == 0)
				prev = prev->prev;
			token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			token->prev = prev;
			token->next = (prev) ? prev->next : shell->start;
			prev = (prev) ? prev : token;
			prev->next->prev = token;
			prev->next = (shell->start->prev) ? prev->next : token;
			shell->start = (shell->start->prev) ? shell->start->prev : shell->start;
		}
		token = token->next;
	}
}

int		next_alloc(char *s, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (s[*i + j] && (s[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (s[*i + j] == '\'' || s[*i + j] == '\"'))
			c = s[*i + j++];
		else if (c != ' ' && s[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (s[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

t_tkn	*next_tkn(char *s, int *i)
{
	t_tkn	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	if (!(token = malloc(sizeof(t_tkn)))
	|| !(token->str = malloc(sizeof(char) * next_alloc(s, i))))
		return (NULL);
	while (s[*i] && (s[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (s[*i] == '\'' || s[*i] == '\"'))
			c = s[(*i)++];
		else if (c != ' ' && s[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if (s[*i] == '\\' && (*i)++)
			token->str[j++] = s[(*i)++];
		else
			token->str[j++] = s[(*i)++];
	}
	token->str[j] = '\0';
	return (token);
}

t_tkn	*tokenize(char *s)
{
	t_tkn	*prev;
	t_tkn	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	skip_if(s, &i);
	while (s[i])
	{
		sep = ignore_sep(s, i);
		next = next_tkn(s, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		arg_type(next, sep);
		skip_if(s, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}
