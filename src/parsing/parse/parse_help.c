/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:19:50 by asalo             #+#    #+#             */
/*   Updated: 2024/07/17 18:29:42 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/tokens.h"

/**
 * @brief "\e[1;33m" => escape (yellow text)
 *          Non printing escape sequence with color.
 *          ANSI escape sequences & printf escape sequenes.
*/
void	put_cmd(t_cmd *cmds)
{
	size_t	i;

	printf("\e[1;33mCOMMANDS\e[0m\n");
	if (!cmds)
		printf("No commands\n");
	while (cmds)
	{
		printf("PATH: %s\n", cmds->path);
		printf("ARGS%d:", !!cmds->av);
		i = 0;
		while (cmds->av && cmds->av[i])
			printf("[%s]", cmds->av[i++]);
		printf("\nREDIRECTIONS:\n");
		put_tkn(cmds->io_redir, 0);
		printf("fd_in: %d\nfd_out: %d\n", cmds->fd_in, cmds->fd_out);
		cmds = cmds->next;
		if (cmds)
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

void	free_cmds(t_cmd *cmds)
{
    t_cmd   *tmp;
    size_t  i;

    while (cmds)
    {
        tmp = cmds->next;
        free(cmds->path);
        i = 0;
        while (cmds->av && cmds->av[i])
            free(cmds->av[i++]);
        free(cmds->av);
        free_tokens(cmds->io_redir);
        if (cmds->fd_in != STDIN_FILENO)
            close(cmds->fd_in);
        if (cmds->fd_out != STDOUT_FILENO)
            close(cmds->fd_out);
        free(cmds);
        cmds = tmp;
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
