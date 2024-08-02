/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:31:04 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/02 11:02:18 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	key_exists(t_env *new, t_data *data)
{
	t_env	*temp;

	temp = data->env_list;
	while (temp != NULL)
	{
		if (ft_strncmp(new->key, temp->key, ft_strlen(new->key)) == 0)
		{
			if (new->value == NULL)
				return (0);
			free(temp->value);
			temp->value = new->value;
			free(new->key);
			free(new);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

void 	key_and_value(t_env *new, char *str, char c)
{
	new->key = ft_strdup_till_c(str, c);
	if (!new->key)
	{
		perror("malloc: ");
		return ;
	}
	if ((ft_strlen(new->key) + 1) < ft_strlen(str))
	{
		new->value = dup_rest(str, ft_strlen(new->key));
		if (!new->value)
		{
			perror("malloc :");
			return;
		}
	}
	else
		new->value = NULL;
	new->next = NULL;
}

void	add_new(t_data *data, char *str)
{
	t_env	*temp;
	t_env	*new;

	temp = data->env_list;
	new = NULL;
	new = malloc(sizeof(t_env));
	if (!new)
		perror("malloc: ");
	key_and_value(new, str, '=');
	printf("%s, %s\n", new->key, new->value);
	if (key_exists(new, data) == 0)
		return ;
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
	data->exit_code->state = 0;
	if (!data->cmds->av[1])
		output_export(data->env_list);
	while (data->cmds->av[i] != NULL)
	{
		if (ft_isalpha(data->cmds->av[i][0]) == 0)
		{
			printf("export: `%s': is not a valid identifier\n",
				data->cmds->av[i]);
			data->exit_code->state = 1;
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
 * 	-  if args 5 first letters are PATH= creates data->paths -array
 *
 *
 *  BUGLIST:
 * 		- FIXED!!
 *  - if arg is export kakka=====ripuli:
 *  	- result: kakka="ripuli"
 * 		- bash: kakka="===ripuli"
 * 		- FIXED!!
 *
 */
