/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:39:40 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/08 11:56:44 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	get_path(t_data *data, t_cmd *cmd)
{
	int		i;
	char	*path;
	char	*temp;

	i = 0;
	cmd->path = NULL;
	if (!cmd->av)
		return ;
	temp = ft_strjoin("/", cmd->av[0]);
	if (data->paths == NULL)
		return ;
	while (data->paths[i] != NULL)
	{
		path = ft_strjoin(data->paths[i], temp);
		if (access(path, F_OK) == 0)
		{
			free(temp);
			cmd->path = path;
			return ;
		}
		free(path);
		i++;
	}
	free(temp);
}

static void	no_path_execute(t_cmd *temp, t_data *data)
{
	if (!temp->av)
		exit(0);
	if (access(temp->av[0], X_OK) == 0)
	{
		if (execve(temp->av[0], temp->av, data->envp) == -1)
			perror("exe: ");
	}
	else
	{
		if (builtin_from_child(data, temp) == 0)
		{
			write_fd(2, WHITE, temp->av[0]);
			write_fd(2, WHITE, ": command not found\n");
		}
	}
	data->exit_code->state = 127;
	exit(data->exit_code->state);
}

void	execute_cmd(t_data *data, int i)
{
	t_cmd	*temp;

	temp = data->cmds;
	while (i > 0)
	{
		temp = temp->next;
		i--;
	}
	get_path(data, temp);
	if (temp->path != NULL && temp->av && ft_strlen(temp->av[0]) >= 1
		&& ft_strncmp(temp->av[0], "env", ft_strlen(temp->av[0]) != 0))
	{
		if (execve(temp->path, temp->av, data->envp) != 0)
			perror("eitoimi\n");
	}
	else
		no_path_execute(temp, data);
}

void	simple_arg(t_data *data)
{
	pid_t	p1;
	int		status;

	status = 0;
	p1 = fork();
	signal(SIGINT, sig_handle_child);
	if (p1 == -1)
		perror("fork");
	if (p1 == 0)
	{
		if (check_redir(data, 0) < 0)
		{
			data->exit_code->state = 1;
			exit(data->exit_code->state);
		}
		execute_cmd(data, 0);
	}
	waitpid(p1, &status, WUNTRACED);
	if (WIFEXITED(status) || WIFSIGNALED(status))
	{
		data->exit_code->state = WEXITSTATUS(status);
	}
}

void	execution(t_data *data)
{
	if (pipes_in_prompt(data) == 0)
	{
		if (is_builtin(data) == 0)
			simple_arg(data);
	}
	if (pipes_in_prompt(data) != 0)
		create_pids(data);
}
