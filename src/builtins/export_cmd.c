/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:31:04 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/21 15:31:07 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	key_exists(char **arr, t_data *data)
{
	t_env	*temp;

	temp = data->env_list;
	while (temp != NULL)
	{
		if (ft_strncmp(arr[0], temp->key, ft_strlen(arr[0])) == 0)
		{
			if (arr[1] == NULL)
				return (0);
			free(temp->value);
			temp->value = NULL;
			temp->value = arr[1];
			return (0);
		}
		temp = temp->next;
	}
	return (-1);
}

char	*get_value(char **arr, int flag)
{
	int		i;
	char	*temp;

	i = 2;
	while (arr[i] != NULL)
	{
		temp = ft_strjoin(arr[1], "=");
		free(arr[1]);
		arr[1] = ft_strjoin(temp, arr[i]);
		free(arr[i]);
		arr[i] = NULL;
		free(temp);
		i++;
	}
	if (flag == -1)
	{
		temp = ft_strjoin(arr[1], "=");
		free(arr[1]);
		arr[1] = ft_strdup(temp);
		free(temp);
	}
	return (arr[1]);
}

char	**key_value(char *str)
{
	char	**arr;
	int		len;
	int		flag;

	len = 0;
	flag = 0;
	if (str[ft_strlen(str) - 1] == '=')
		flag = -1;
	arr = ft_split(str, '=');
	while (arr[len] != NULL)
		len++;
	if (len < 3)
		return (arr);
	arr[1] = get_value(arr, flag);
	return (arr);
}

void	add_new(t_data *data, char *str)
{
	t_env	*temp;
	t_env	*new;
	char	**temp_arr;

	new = NULL;
	temp_arr = key_value(str);
	if (!temp_arr)
		perror("malloc");
	if (key_exists(temp_arr, data) == 0)
		return ;
	new = malloc(sizeof(t_env));
	if (!new)
		perror("malloc: ");
	new->key = ft_strdup(temp_arr[0]);
	printf("new key %s\n\n", new->key);
	if (temp_arr[1])
		new->value = ft_strdup(temp_arr[1]);
	else
		new->value = NULL;
	printf("new value %s\n\n", new->value);
	new->next = NULL;
	free_array(temp_arr);
	temp = data->env_list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	output_export(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr != NULL)
	{
		if (ptr->value)
			printf("declare -x %s=\"%s\"\n", ptr->key, ptr->value);
		else
			printf("declare -x %s\n", ptr->key);
		ptr = ptr->next;
	}
}

void	export_cmd(t_data *data)
{
	int	i;

	i = 1;
	data->exit_code = 0;
	if (!data->cmds->av[1])
		output_export(data->env_list);
	while (data->cmds->av[i] != NULL)
	{
		if (ft_isalpha(data->cmds->av[i][0]) == 0)
		{
			printf("export: `%s': is not a valid identifier\n",
				data->cmds->av[i]);
			data->exit_code = 1;
		}
		else
		{
			add_new(data, data->cmds->av[i]);
			if (ft_strncmp("PATH=", data->cmds->av[i], 5) == 0)
			{
				create_paths(data);
			}
		}
		i++;
	}
}

/*
 * DELETE THIS
 *
 * export without arguments:
 *  - outputs export list
 *  - if there are vars in export list that has no value, output only keys
 *
 * export with arguments:
 *  - arg needs to start with alphabet
 *  - arg needs to include '=' to make it key/value pair
 *      - if it has no '=' it will be only "key" and value is "NULL"
 *  -  if arg is existing key it has to modify existing variable
 *  -  if arg is existing key but arg has no '=' it does nothing
 *  -  if arg is existing key and has '=' but no value after it makes value ""
 *  -  if arg has multiple '=' it will be splitted from first '='
 * 		- first word will be key, and rest of the string will be value
 * 	-  if args 5 first letters are PATH= creates data->paths -array
 * 
 * 
 *  BUGLIST:
 *  - if arg is export kakka=====ripuli:
 *  	- result: kakka="ripuli"
 * 		- bash: kakka="===ripuli"
 * 
 */