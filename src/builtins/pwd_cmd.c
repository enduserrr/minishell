/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:45:34 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/02 11:02:27 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*
 * DELETE THIS
 *
 * - outputs current pwd
 * - should work with | or other args
 * - "pwd" "randomshit" --> should output pwd
 * - "pwd" | wc -l --> lines of pwd
 * - "pwd"
 *
 */
