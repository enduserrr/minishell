#include "../incs/minishell.h"

int	ft_arraylen(char **arr)
{
	int	len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}

void	free_all(t_data *data)
{
	if (data->paths != 0)
		delete_paths(data);
	if (data->path)
		free(data->path);
	free_env(data);
}

void	free_env(t_data *data)
{
	t_env	*current;
	t_env	*temp;

	current = data->env_list;
	while (current != NULL)
	{
		temp = current->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = temp;
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
