/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:53:27 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/08 17:55:00 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	write_to_pipe(char *delimiter, int *h_fd)
{
	char	*line;

	line = NULL;
	signal(SIGINT, sig_handle_heredoc);
	write(1, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	if (!line || *signal_trigger() == 1)
	{
		if (line)
			free(line);
		if (*signal_trigger() == 1)
			return (-2);
		write(1, "\n", 1);
		return (-1);
	}
	if ((ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0))
	{
		free(line);
		return (-1);
	}
	write(h_fd[1], line, ft_strlen(line));
	free(line);
	return (0);
}

void	h_loop(int *h_fd, char *delim)
{
	int	i;
	int	*trigger;

	i = 0;
	trigger = NULL;
	signal(SIGINT, sig_handle_heredoc);
	while (1)
	{
		i = write_to_pipe(delim, h_fd);
		if (i == -2)
		{
			trigger = signal_trigger();
			free(trigger);
			exit(1);
		}
		if (i == -1)
			break ;
	}
}

int	heredoc_handler(t_cmd *temp, char *delimiter, int fd_out)
{
	int			h_fd[2];
	static int	flag;
	int			*trigger;

	flag = 0;
	if (pipe(h_fd) == -1)
		perror("pipe: ");
	h_loop(h_fd, delimiter);
	trigger = signal_trigger();
	free(trigger);
	close(h_fd[1]);
	if (dup2(h_fd[0], STDIN_FILENO) == -1)
		perror("dup2: ");
	close(h_fd[0]);
	if (temp->io_redir->next != NULL)
	{
		temp->io_redir = temp->io_redir->next;
		check_out(temp, fd_out);
	}
	if (!temp->av)
		return (-1);
	return (1);
}
