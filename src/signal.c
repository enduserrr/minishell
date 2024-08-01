/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:59:04 by asalo             #+#    #+#             */
/*   Updated: 2024/08/01 11:45:22 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_sig_status = 0;

void	sig_handle_nl(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

int *signal_trigger(void)
{
	static int	*triggered;

	if (!triggered)
	{
		triggered = (int *)malloc(sizeof(int));
		*triggered = 0;
	}
	return (triggered);
}

void	sig_handle_child(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, sig_handle_child);
	}
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handle_heredoc(int sig)
{
	int	*triggered;

	triggered = signal_trigger();
	if (sig == SIGINT)
	{
		*triggered = 1;
		signal(SIGINT, sig_handle_heredoc);
	}
}

