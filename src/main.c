/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/18 11:55:21 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/tokens.h"

static void show_tokens(t_token *tokens)
{
    t_token *current = tokens;
    while (current)
    {
        printf("Token: id=%d, content=%s\n", current->id, current->content);
        current = current->next;
    }
}

static void show_commands(t_cmd *cmds)
{
    t_cmd *current = cmds;
    while (current)
    {
        printf("Command: path=%s\n", current->path);
        printf("Arguments:\n");
        for (char **arg = current->av; arg && *arg; ++arg)
            printf("  %s\n", *arg);
        printf("Input Redirection: %d\n", current->fd_in);
        printf("Output Redirection: %d\n", current->fd_out);
        printf("Builtin: %d\n", current->builtin);
        current = current->next;
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <command_string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *input = argv[1];
    int status = 0;
    t_token *tokens = tokenizer(&status, input);
    if (!tokens)
    {
        fprintf(stderr, "Failed to tokenize input.\n");
        return EXIT_FAILURE;
    }
    printf("Tokens:\n");
    show_tokens(tokens);
    t_cmd *cmds = parse(&status, tokens);
    if (!cmds)
    {
        fprintf(stderr, "Failed to parse tokens.\n");
        free_tokens(tokens);
        return EXIT_FAILURE;
    }
    printf("Commands:\n");
    show_commands(cmds);
    free_tokens(tokens);
    free_cmds(cmds);
    return EXIT_SUCCESS;
}