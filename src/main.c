/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:06 by asalo             #+#    #+#             */
/*   Updated: 2024/08/05 10:11:36 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include <bits/sigaction.h>
#define SA_NODEFER 0x40000000
#include <setjmp.h>
#include <termios.h>
#include <term.h>

void 	process_cmds(t_data *data)
{
	if (data->cmds == NULL)
        return ;
    if (is_builtin(data) != 0)
			return ;
	else
        execution(data);
}

// void restore_terminal_settings(struct termios *original)
// {
//     tcsetattr(STDIN_FILENO, TCSANOW, original);
// }

// void configure_terminal(void)
// {
//     struct termios new_termios;
//     tcgetattr(STDIN_FILENO, &global_termios); // Save the original settings
//     new_termios = global_termios;
//     // Disable canonical mode
//     new_termios.c_lflag &= ~(ICANON);
//     new_termios.c_cc[VMIN] = 1;
//     new_termios.c_cc[VTIME] = 0;
//     tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
// }

// void *read_input()
// {
//     static char buffer[1024];
//     int n;

//     while (1)
//     {
//         printf("$> ");
//         fflush(stdout);

//         n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

//         if (n == -1)
//         {
//             perror("read");
//             exit(EXIT_FAILURE);
//         }
//         else if (n == 0)
//         {
//             // End-of-file detected
//             printf("EOF detected\n");
//             return ((void *) 1);
//         }
//         else
//         {
//             buffer[n] = '\0'; // Null-terminate the input

//             if (strcmp(buffer, "") == 0)
//             {
//                 printf("Empty string detected\n");
//                 return ((void *)0);
//             }
//             else
//             {
//                 printf("Input: %s\n", buffer);
//                 return ((void *)0);
//             }
//         }
//     }
// }


void run(t_data *data, t_exit *state)
{
    char    *input;
    t_token *tokens;

    while(1)
    {
        // read_input();
        signal(SIGINT, signal_handler);
        input = readline("$> ");
        if (!input)
        {
            write_fd(1, WHITE, "exit\n");
            break ;
        }
        if (*input == '\0')
        {
            write_fd(2, WHITE, "command unknown\n");
            free(input);
            continue ;
        }
        add_history(input);
        tokens = ft_token(state, input);
        data->cmds = ft_parse(state, tokens);
        process_cmds(data);
        free_commands(data->cmds);
    }
    free_all(data);
}

static void	config_terminal(void)
{
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~(ICANON);
    new_term.c_cc[VMIN] = 2;
    new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

int main(int ac, char **av, char **envp)
{
    (void)av;
	t_data          data;
    static t_exit   exit_state;

    if (ac != 1)
        return (write_fd(1, RED, "No args accepted\n"), 0);
    signal(SIGQUIT, SIG_IGN);
    exit_state = (t_exit){0};
    data = (t_data){0};
    data.envp = envp;
    data.exit_code = &exit_state;
    create_env_list(&data);
    create_paths(&data);
    config_terminal();
    write_fd(1, GREEN, WLCM);
	run(&data, &exit_state);
	return (0);
}
