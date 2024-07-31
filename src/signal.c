/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:59:04 by asalo             #+#    #+#             */
/*   Updated: 2024/07/31 19:14:22 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// static volatile sig_atomic_t g_signl = 0;


void	rl_handler(int sig)
{
    write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void sigterm_handler(int sig)
{
    // SIGTERM or other signals if needed
    (void)sig;
    // Handle if necessary
}

void sigquit_handler(int sig)
{
    (void)sig;
}

static void setup_signal_handlers(void)
{
    struct sigaction sa;

    // Handle SIGINT (Ctrl-C)
    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_handler = rl_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    // Handle SIGQUIT (Ctrl-\), ignore it
    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigquit_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}
