/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:19:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/20 12:07:54 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/tokens.h"

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

void    eval_commands(t_token *tokens)
{
    while (tokens)
    {
        while (tokens && tokens->id != WORD && tokens->id != COMMAND)
            tokens = tokens->next;
        if (!tokens)
            return ;
        tokens->id = COMMAND;
        while (tokens &&  tokens->id != PIPE)
            tokens = tokens->next;
    }
}

t_cmd   *parse(int *status, t_token *tokens)
{
    t_cmd   *commands;

    if (expand_tkns(*status, &tokens) == RETURN_FAILURE || !tokens)
    {
        *status = EXIT_FAILURE;/*Meaby rid this & exit set based on return state*/
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

// static void remove_quotes(t_token *tokens)
// {
//     size_t  i;
//     char    q;

//     while (tokens)
//     {
//         q = 0;
//         i = -1;
//         while (tokens->content[++i])
//         {
//             if (!q && ft_strchr("\'\"", tokens->content[i]))
//                 q = tokens->content[i];
//             else if (tokens->content[i] == q)
//                 q = 0;
//             else
//                 continue ;
//             ft_strcpy(&tokens->content[i], &tokens->content[i + 1]);
//             i--;
//         }
//         tokens = tokens->next;
//     }
// }

// void    eval_commands(t_token *tokens)
// {
//     while (tokens)
//     {
//         while (tokens && tokens->id != WORD && tokens->id != COMMAND)
//             tokens = tokens->next;
//         if (!tokens)
//             return ;
//         tokens->id = COMMAND;
//         while (tokens &&  tokens->id != PIPE)
//             tokens = tokens->next;
//     }
// }

// t_cmd   *parse(int *status, t_token *tokens)
// {
//     t_cmd   *commands;

//     if (expand_tkns(*status, &tokens) == RETURN_FAILURE || !tokens)
//     {
//         *status = EXIT_FAILURE;/*Meaby rid this & exit set based on return state*/
//         return (free_tokens(tokens), NULL);
//     }
//     eval_commands(tokens);
//     remove_quotes(tokens);
//     commands = create_cmd_table(tokens);
//     if (!commands)
//     {
//         *status = MEM_ERR;
//         return (free_tokens(tokens), NULL);
//     }
//     return (commands);
// }