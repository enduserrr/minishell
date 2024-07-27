/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:07:21 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/25 19:07:23 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int check_out(t_cmd *temp, int fd)
{
    //printf("[redir out TRUE]: id: %d\n", temp->io_redir->id);
    fd = open(temp->io_redir->content, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd == -1)
    {
        perror("dup: ");
        return (0);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup: ");
        return (0);
    }
    close(fd);
    return (2);
}

int check_in(t_cmd *temp, int fd, int fd_out)
{
    //printf("[redir in TRUE]: id: %d\n", temp->io_redir->id);
    fd = open(temp->io_redir->content, O_RDONLY);
    if (fd == -1)
    {
        perror("open: ");
        return (0);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup: ");
        return (0);
    }
    if (temp->io_redir->next != NULL)
    {
        temp->io_redir = temp->io_redir->next;
        check_out(temp, fd_out);
    }
    close(fd);
    return (1);
}

int check_redir(t_data *data, int i)
{
    int     fd_in;
    int     fd_out;
    t_cmd   *temp;

    //printf("[check_redir start]\n");
    fd_in = 0;
    fd_out = 0;
    temp = data->cmds;
    while(i > 0)
    {
        temp = temp->next;
        i --;
    }
    if (temp->io_redir && temp->io_redir->id == 5)
        return (check_in(temp, fd_in, fd_out));
    else if (temp->io_redir && temp->io_redir->id == 9)
        return (check_out(temp, fd_out));
    //printf("[redir FALSE]\n[check_redir end]\n");
    return (0);
}
