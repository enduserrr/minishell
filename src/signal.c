/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:59:04 by asalo             #+#    #+#             */
/*   Updated: 2024/07/31 11:41:12 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// static volatile sig_atomic_t g_signl = 0;

// void handle_sigint(int sig)
// {
//     (void)sig;
//     g_signl = SIGINT;
//     write(1, "\n", 1);
//     rl_on_new_line();
//     rl_replace_line("", 0);
//     rl_redisplay();
// 	write(STDOUT_FILENO, "$> ", 3);
// }

// void    handle_sigterm(int sig)
// {
//     (void)sig;
//     g_signl = SIGTERM;
//     write(1, "\n", 1);
//     rl_on_new_line();
//     rl_replace_line("", 0);
//     rl_redisplay();
// 	write(1, "exit\n", 5);
// }

// void handle_sigquit(int sig)
// {
//     (void)sig;
//     g_signl = SIGQUIT;
// }

// void setup_signal_handling(void)
// {
//     struct sigaction sa;

//     sa.sa_handler = handle_sigint;
//     sigemptyset(&sa.sa_mask);
//     sa.sa_flags = SA_RESTART;
//     if (sigaction(SIGINT, &sa, NULL) == -1)
//     {
//         perror("sigaction");
//         exit(EXIT_FAILURE);
//     }
//     sa.sa_handler = handle_sigquit;
//     if (sigaction(SIGQUIT, &sa, NULL) == -1)
//     {
//         perror("sigaction");
//         exit(EXIT_FAILURE);
//     }
// }

// void restore_terminal_settings(const struct termios *orig_termios)
// {
//     if (tcsetattr(STDIN_FILENO, TCSANOW, orig_termios) == -1)
//     {
//         perror("tcsetattr");
//         exit(EXIT_FAILURE);
//     }
// }

// struct termios setup_terminal(void)
// {
//     struct termios orig_termios;
//     struct termios new_termios;

//     // Save original terminal settings
//     if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
//     {
//         perror("tcgetattr");
//         exit(EXIT_FAILURE);
//     }
//     new_termios = orig_termios;
//     // Modify terminal settings for non-canonical mode
//     new_termios.c_lflag &= ~(ICANON | ECHO);
//     if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1)
//     {
//         perror("tcsetattr");
//         exit(EXIT_FAILURE);
//     }
//     return (orig_termios);
// }

// void setup_terminal(void)
// {
//     static struct termios	og_termios;
// 	struct termios			new_termios;

//     if (tcgetattr(STDIN_FILENO, &og_termios) == -1)
//     {
//         perror("tcgetattr");
//         exit(EXIT_FAILURE);
//     }
//     new_termios = og_termios;
//     new_termios.c_lflag &= ~(ICANON | ECHO);
//     if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1)
//     {
//         perror("tcsetattr");
//         exit(EXIT_FAILURE);
//     }
//     atexit(restore_terminal_settings);
// }
