/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:19:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/21 11:39:37 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

void	put_cmd(t_cmd *commands)
{
	size_t	i;

	printf("COMMANDS\n");
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
		printf("FD_IN %d\nFD_OUT: %d\n", commands->fd_in, commands->fd_out);
		commands = commands->next;
		if (commands)
			printf("\033[48;5;19m\033[97m↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓\e[0m\n");
	}
}

static void remove_quotes(t_token *tokens)
{
    size_t  i;
    char    q;

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


t_cmd   *parse(int *status, t_token *tokens)
{
    t_cmd   *commands;

    if (expand_tkns(*status, &tokens) == RETURN_FAILURE || !tokens)
    {
        *status = EXIT_FAILURE;
        return (free_tokens(tokens), NULL);
    }
    eval_commands(tokens);
    remove_quotes(tokens);
    commands = create_cmd_table(tokens);
    put_cmd(commands);
    if (!commands)
    {
        *status = MEM_ERR;
        return (free_tokens(tokens), NULL);
    }
    return (commands);
}
