/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:19:50 by asalo             #+#    #+#             */
/*   Updated: 2024/07/18 10:51:28 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/tokens.h"

/**
 * @brief "\e[1;33m" => escape (yellow text)
 *          Non printing escape sequence with color.
 *          ANSI escape sequences & printf escape sequenes.
*/
void	put_cmd(t_cmd *commands)
{
	size_t	i;

	printf("\e[1;33mCOMMANDS\e[0m\n");
	if (!commands)
		printf("No commands\n");
	while (commands)
	{
		printf("PATH: %s\n", commands->path);
		printf("ARGS%d:", !!commands->av);
		i = 0;
		while (commands->av && commands->av[i])
			printf("[%s]", commands->av[i++]);
		printf("\nREDIRECTIONS:\n");
		put_tkn(commands->io_redir, 0);
		printf("fd_in: %d\nfd_out: %d\n", commands->fd_in, commands->fd_out);
		commands = commands->next;
		if (commands)
			printf("\e[0;33m↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓\e[0m\n");
	}
}

static t_cmd	*new_cmd(size_t av_count)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
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
	t_token	*tmp;
	size_t	count;

	count = 0;
	tmp = tokens;
	while (tmp && tmp->id != PIPE)
	{
		if (tmp->id == COMMAND || tmp->id == WORD)
			count++;
		tmp = tmp->next;
	}
	commands = new_cmd(count);
	last = commands;
	while (last)
	{
		while (tokens && tokens->id != PIPE)
			tokens = tokens->next;
		if (!tokens)
			return (commands);
		tokens = tokens->next;
		last->next = new_cmd(count);
		last = last->next;
	}
	return (free_cmds(commands), NULL);
}
