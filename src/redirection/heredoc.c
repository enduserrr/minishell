/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:53:27 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/01 11:46:12 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int    write_to_pipe(char *delimiter, int *h_fd)
{
    char    *line;

    line = NULL;
    signal(SIGINT, sig_handle_heredoc);
    write(1, "> ", 2);
    line = get_next_line(STDIN_FILENO);
    if (!line)
        return (-1);
    if ((ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
        || *signal_trigger() == 1)
    {
        free(line);
        return (-1);
    }
    write(h_fd[1], line, ft_strlen(line));
    free(line);
    return (0);
}

int    heredoc_handler(t_cmd *temp, char *delimiter, int fd_out)
{
    int     h_fd[2];
    int     *trigger;

    if (pipe(h_fd) == -1)
        perror("pipe: ");
    signal(SIGINT, sig_handle_heredoc);
    while (1)
    {
        if (write_to_pipe(delimiter, h_fd) != 0)
            break ;
    }
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
    return (1);
}
