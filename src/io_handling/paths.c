#include "../../incs/minishell.h"

void	delete_paths(t_data *data)
{
	free_array(data->paths);
	data->paths = NULL;
}

void	create_paths(t_data *data)
{
	t_env	*temp;

	temp = data->env_list;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, "PATH", 4) == 0)
		{
			data->paths = ft_split(temp->value, ':');
			if (!data->paths)
				perror("malloc: ");
			break ;
		}
		temp = temp->next;
	}
}
