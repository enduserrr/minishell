/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:19:06 by asalo             #+#    #+#             */
/*   Updated: 2024/08/02 11:28:54 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

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

t_cmd   *ft_parse(t_exit *state, t_token *tokens)
{
    t_cmd   *commands;

    if (ft_expand(state, &tokens) == 1 || !tokens)
    {
        state->state = EXIT_FAILURE;
        return (free_tokens(tokens), NULL);
    }
    check_commands(tokens);
    remove_quotes(tokens);
    commands = command_table(tokens, state);
    put_command(commands);
    if (!commands)
    {
        state->state = MEM_ERR;
        return (free_tokens(tokens), NULL);
    }
    return (commands);
}
