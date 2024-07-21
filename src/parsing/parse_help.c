/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:19:50 by asalo             #+#    #+#             */
/*   Updated: 2024/07/21 13:02:18 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

static size_t	count_av_tkns(t_token *tokens)
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

static t_cmd	*new_cmd(size_t av_count)
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
	new->builtin = B_NO;
	new->next = NULL;
	if (av_count)
		new->av = ft_calloc(av_count + 1, sizeof(char *));
	if (av_count && !new->av)
		return (free(new), NULL);
	return (new);
}

ssize_t set_char(char *s, char c, ssize_t i)
{
    if (c == '/' && i < 0)
		return (ft_strlen(s));
	if (!s || i < 0 || i > (ssize_t)ft_strlen(s))
		return (-1);
	s[i] = c;
	return (i);
}

void	free_cmds(t_cmd *commands)
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

	commands = new_cmd(count_av_tkns(tokens));
	last = commands;
	while (last)
	{
		while (tokens && tokens->id != PIPE)
			tokens = tokens->next;
		if (!tokens)
			return (commands);
		tokens = tokens->next;
		last->next = new_cmd(count_av_tkns(tokens));
		last = last->next;
	}
	return (free_cmds(commands), NULL);
}
