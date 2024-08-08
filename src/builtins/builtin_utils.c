/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:30:17 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/08 11:48:42 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*ft_strdup_till_c(const char *s1, char c)
{
	char	*dup;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s1[len] != '\0')
	{
		if (s1[len] == c)
			break ;
		len++;
	}
	if (len == 0)
		i++;
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*dup_rest(char *s, int start)
{
	int		i;
	int		start1;
	char	*temp;

	i = 0;
	start1 = start;
	while (s[start1] != '\0')
	{
		i++;
		start1++;
	}
	printf("i: %d", i);
	temp = malloc((i + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	start++;
	while (s[start] != '\0')
	{
		temp[i] = s[start];
		printf("temp[i]: %c\n", temp[i]);
		start++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

int	builtin_from_child(t_data *data, t_cmd *cmds)
{
	size_t	len;

	if (!data->cmds->av)
		return (0);
	len = ft_strlen(cmds->av[0]);
	if (ft_strncmp(cmds->av[0], "env", len) == 0)
		return (env_cmd(data), 1);
	if (ft_strncmp(cmds->av[0], "echo", len) == 0)
		return (echo_cmd(data), 1);
	if (ft_strncmp(cmds->av[0], "pwd", len) == 0)
		return (pwd_cmd(data), 1);
	if (ft_strncmp(cmds->av[0], "export", len) == 0)
		return (export_cmd(data), 1);
	return (0);
}

int	is_builtin(t_data *data)
{
	size_t	len;

	if (!data->cmds->av)
		return (0);
	len = ft_strlen(data->cmds->av[0]);
	if (ft_strncmp(data->cmds->av[0], "exit", len) == 0)
		return (exit_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "cd", len) == 0)
		return (cd_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "env", len) == 0)
		return (env_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "echo", len) == 0)
		return (echo_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "pwd", len) == 0)
		return (pwd_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "unset", len) == 0)
		return (unset_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "export", len) == 0)
		return (export_cmd(data), 1);
	return (0);
}

void	update_pwds(t_data *data, char *old_pwd)
{
	char	*pwd;
	t_env	*temp;

	pwd = getcwd(NULL, 0);
	temp = data->env_list;
	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->key, "OLDPWD", 6) == 0)
		{
			free(temp->value);
			temp->value = NULL;
			temp->value = old_pwd;
		}
		else if (ft_strncmp(temp->key, "PWD", 3) == 0)
		{
			free(temp->value);
			temp->value = NULL;
			temp->value = pwd;
		}
		temp = temp->next;
	}
}
