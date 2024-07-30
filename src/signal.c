/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:59:04 by asalo             #+#    #+#             */
/*   Updated: 2024/07/30 16:08:09 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

volatile sig_atomic_t g_signal_status = 0;

void	sig_handler_child(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = SIGINT;
        write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGTERM)
	{
		g_signal_status = SIGTERM;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		write(1, "exit\n", 5);
	}
}

void	sigint_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
        write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signal_handlers(void (*int_)(int))
{
	rl_catch_signals = 1;
	signal(SIGINT, int_);
	signal(SIGTERM, int_);
}
