/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:59:04 by asalo             #+#    #+#             */
/*   Updated: 2024/08/09 15:04:36 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/general.h"

void	sig_handle_nl(int sig)
{	
	if (sig == SIGINT)
		write(1, "\n", 1);
}

int	*signal_trigger(void)
{
	static int	*trigger;

	if (!trigger)
	{
		trigger = (int *)malloc(sizeof(int));
		*trigger = 0;
	}
	return (trigger);
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
	int	*trigger;

	trigger = signal_trigger();
	if (sig == SIGINT)
	{
		*trigger = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
