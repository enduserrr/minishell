/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:06 by asalo             #+#    #+#             */
/*   Updated: 2024/08/05 13:50:54 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../incs/minishell.h"
// #include <bits/sigaction.h>
// #define SA_NODEFER 0x40000000
// #include <setjmp.h>
// #include <termios.h>
// #include <term.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <string.h>
#include "../incs/minishell.h"

void process_cmds(t_data *data)
{
    if (data->cmds == NULL)
        return ;
    if (is_builtin(data) != 0)
        return ;
    else
        execution(data);
}

void restore_terminal_settings(struct termios *original)
{
    tcsetattr(STDIN_FILENO, TCSANOW, original);
}

void configure_terminal(struct termios *original)
{
    struct termios new_termios;

    tcgetattr(STDIN_FILENO, original);
    new_termios = *original;
    new_termios.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void run(t_data *data, t_exit *state, struct termios *original)
{
    char    *input;
    t_token *tokens;

    while(1)
    {
        signal(SIGINT, signal_handler);
        input = readline("$> ");
        if (input == NULL)
        {
            write_fd(1, WHITE, "exit\n");
            break ;
        }
        else
        {
            add_history(input);
            tokens = ft_token(state, input);
            data->cmds = ft_parse(state, tokens);
            process_cmds(data);
            free_commands(data->cmds);
        }
    }
    free_all(data);
    restore_terminal_settings(original);
}

int main(int ac, char **av, char **envp)
{
    (void)av;
    t_data data;
    static t_exit exit_state;
    struct termios original;

    if (ac != 1)
        return (write_fd(1, RED, "No args accepted\n"), 0);
    signal(SIGQUIT, SIG_IGN);
    exit_state = (t_exit){0};
    data = (t_data){0};
    data.envp = envp;
    data.exit_code = &exit_state;
    create_env_list(&data);
    create_paths(&data);
    configure_terminal(&original);
    write_fd(1, GREEN, WLCM);
    run(&data, &exit_state, &original);
    return (0);
}
