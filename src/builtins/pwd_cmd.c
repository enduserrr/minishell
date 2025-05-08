#include "../../incs/minishell.h"

char	*ft_get_cwd(t_env *env)
{
	t_env	*temp;
	char	*str;

	temp = env;
	str = NULL;
	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->key, "PWD", ft_strlen(temp->key)) == 0)
		{
			str = ft_strdup(temp->value);
			if (!str)
				perror("malloc: ");
			break ;
		}
		temp = temp->next;
	}
	return (str);
}

void	pwd_cmd(t_data *data)
{
	char	*pwd;

	data->exit_code->state = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = ft_get_cwd(data->env_list);
		if (!pwd)
		{
			perror("pwd: ");
			return ;
		}
	}
	printf("%s\n", pwd);
	free(pwd);
}
