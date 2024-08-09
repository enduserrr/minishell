/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:37:44 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/09 09:12:19 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	echo_redir(t_data *data)
{
	int	fd_out;

	fd_out = -1;
	if (data->cmds->io_redir->id == 9)
	{
		fd_out = open(data->cmds->io_redir->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
		printf("%d\n", fd_out);
		if (fd_out == -1)
			return (perror("open :"), -1);
	}
	else
	{
		fd_out = open(data->cmds->io_redir->content,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd_out == -1)
			return (perror("open :"), -1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		return (perror("dup: "), close(fd_out), -1);
	}
	close(fd_out);
	return (0);
}

static void	*n_check(char *s)
{
	size_t	i;

	i = 1;
	if (ft_strlen(s) == 2)
		return ((void *)0);
	else
	{
		while(s[i])
		{
			if (s[i] != 'n')
				return ((void *)1);
			i++;
		}
	}
	return (NULL);
}

static void	output_echo(t_data *data)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (data->cmds->av[1] != NULL && ft_strncmp(data->cmds->av[1], "-n",
			2) == 0 && n_check(data->cmds->av[1]) == NULL)
	{
		flag = 1;
		i++;
	}
	while (data->cmds->av[i] != NULL)
	{
		ft_putstr_fd(data->cmds->av[i], STDOUT_FILENO);
		if (data->cmds->av[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (flag == 0)
		printf("\n");
	data->exit_code->state = 0;
}

void	echo_cmd(t_data *data)
{
	int	orig_fd;

	orig_fd = -1;
	if (data->cmds->io_redir && (data->cmds->io_redir->id == 9
			|| data->cmds->io_redir->id == 33))
	{
		orig_fd = dup(STDOUT_FILENO);
		if (orig_fd == -1 || echo_redir(data) == -1)
		{
			close(orig_fd);
			data->exit_code->state = 1;
			return ;
		}
	}
	output_echo(data);
	if (orig_fd != -1)
	{
		if (dup2(orig_fd, STDOUT_FILENO) == -1)
			perror("dup2: ");
		close(orig_fd);
	}
}
