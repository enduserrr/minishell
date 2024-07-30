/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:19:50 by asalo             #+#    #+#             */
/*   Updated: 2024/07/23 11:29:26 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

static size_t	count_tokens(t_token *tokens)
{
	size_t	i;

	i = 0;
	while (tokens && tokens->id != PIPE)
	{
		if (tokens->id == COMMAND || tokens->id == WORD)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

static t_cmd	*init_command(size_t av_count)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->path = NULL;
	new->av = NULL;
	new->io_redir = NULL;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->next = NULL;
	if (av_count)
		new->av = ft_calloc(av_count + 1, sizeof(char *));
	if (av_count && !new->av)
		return (free(new), NULL);
	return (new);
}

/**
 * @brief	Removes specified token from t_token linked list
 *			and removes the spaces that was allocated to it.
 */
t_token	*rm_token(t_token **top, t_token *remove)
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

void	free_commands(t_cmd *commands)
{
    t_cmd   *tmp;
    size_t  i;

    while (commands)
    {
        tmp = commands->next;
        free(commands->path);
        i = 0;
        while (commands->av && commands->av[i])
            free(commands->av[i++]);
        free(commands->av);
        free_tokens(commands->io_redir);
        if (commands->fd_in != STDIN_FILENO)
            close(commands->fd_in);
        if (commands->fd_out != STDOUT_FILENO)
            close(commands->fd_out);
        free(commands);
        commands = tmp;
    }
}

t_cmd	*alloc_cmd(t_token *tokens)
{
	t_cmd	*commands;
	t_cmd	*last;

	commands = init_command(count_tokens(tokens));
	last = commands;
	while (last)
	{
		while (tokens && tokens->id != PIPE)
			tokens = tokens->next;
		if (!tokens)
			return (commands);
		tokens = tokens->next;
		last->next = init_command(count_tokens(tokens));
		last = last->next;
	}
	return (free_commands(commands), NULL);

}
