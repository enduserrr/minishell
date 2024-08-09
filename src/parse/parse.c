/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:19:06 by asalo             #+#    #+#             */
/*   Updated: 2024/08/09 12:52:59 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

char	*find_env(char *env, t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(env, tmp->key, ft_strlen(env)) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

static void	remove_quotes(t_token *tokens)
{
	size_t	i;
	char	q;

	while (tokens)
	{
		q = 0;
		i = -1;
		while (tokens->content[++i])
		{
			if (!q && ft_strchr("\'\"", tokens->content[i]))
				q = tokens->content[i];
			else if (tokens->content[i] == q)
				q = 0;
			else
				continue ;
			ft_strcpy(&tokens->content[i], &tokens->content[i + 1]);
			i--;
		}
		tokens = tokens->next;
	}
}

static void	split_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	*check_spaces(t_token **tokens, int i, t_exit *state)
{
	t_token	*current;
	t_token	*new_next;
	char	**split_content;

	current = *tokens;
	while (current)
	{
		split_content = ft_split(current->content, ' ');
		if (!split_content)
			return ((void *)1);
		free(current->content);
		current->content = ft_strdup(split_content[0]);
		while (split_content[i])
		{
			new_next = new_token(ft_strdup(split_content[i]), state);
			if (!new_next)
				return (free(split_content), NULL);
			new_next->next = current->next;
			current->next = new_next;
			current = new_next;
			i++;
		}
		current = current->next;
	}
	return (split_free(split_content), NULL);
}

t_cmd	*ft_parse(t_exit *state, t_token *tokens, t_env *env)
{
	t_cmd	*commands;

	if (ft_expand(state, &tokens, env) == 1 || !tokens)
	{
		if (!tokens)
			return (NULL);
		state->state = EXIT_FAILURE;
		return (free_tokens(tokens), NULL);
	}
	if (ft_strchr(tokens->content, ' '))
	{
		if (check_spaces(&tokens, 1, state) == (void *)1)
			set_err(MEM_ERR, "splitting token by spaces", state);
	}
	check_commands(tokens);
	remove_quotes(tokens);
	commands = command_table(tokens, state);
	if (!commands)
	{
		state->state = MEM_ERR;
		return (free_tokens(tokens), NULL);
	}
	return (commands);
}
