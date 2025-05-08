#include "../../incs/minishell.h"

void	perror_exit(t_data *data, char *s, int fd)
{
	write(2, s, ft_strlen(s));
	perror(": ");
	if (fd != -1)
		close(fd);
	data->exit_code->state = 1;
	exit(data->exit_code->state);
}

int	pipes_in_prompt(t_data *data)
{
	t_cmd	*temp;
	int		flag;

	temp = data->cmds;
	flag = 0;
	while (temp->next)
	{
		temp = temp->next;
		flag ++;
	}
	data->pipe_amount = flag;
	return (flag);
}

void	next_pipe(t_data *data, int *prev_fd, int *fd, int i)
{
	if (prev_fd[0] != -1)
	{
		close(prev_fd[0]);
		close(prev_fd[1]);
	}
	if (i < data->pipe_amount)
	{
		prev_fd[0] = fd[0];
		prev_fd[1] = fd[1];
	}
}
