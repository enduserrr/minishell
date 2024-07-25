/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:19:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/25 11:35:14 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

static void remove_quotes(t_token *tokens)
{
    size_t  i;
    char    reference;

    while (tokens)
    {
        reference = 0;
        i = -1;
        while (tokens->content[++i])
        {
            if (!reference && ft_strchr("\'\"", tokens->content[i]))
                reference = tokens->content[i];
            else if (tokens->content[i] == reference)
                reference = 0;
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
