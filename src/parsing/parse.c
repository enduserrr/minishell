/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:19:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/23 12:37:32 by asalo            ###   ########.fr       */
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

t_cmd   *ft_parse(int *status, t_token *tokens)
{
    t_cmd   *commands;

    if (expand_tokens(*status, &tokens) == RETURN_FAILURE || !tokens)
    {
        *status = EXIT_FAILURE;
        return (free_tokens(tokens), NULL);
    }
    check_commands(tokens);
    remove_quotes(tokens);
    commands = command_table(tokens);
    put_command(commands);
    if (!commands)
    {
        *status = MEM_ERR;
        return (free_tokens(tokens), NULL);
    }
    return (commands);
}
