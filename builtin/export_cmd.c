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

#include "../includes/minishell.h"

/*
 * Export without commands shows envlist like export does:
 *  - declare -x USER="eleppala"
 * export with args adds valid args to variable list
 *  - arg needs to start with letter
 *
 * toimii nyt usealla argumentilla kerralla
 * muokkaa jo olemassa olevan argumentin arvoa
 * tarkistaa etta argumentti on kelpo
 *
 * Puutteet:
 *  - export lista aakkosjarjestykseen
 *  - uuden variablen lisaaminen aakkosjarjestettyyn listaan
 */

int	key_exists(char **arr, t_tools *tools)
{
	t_env	*temp;

	temp = tools->env_list;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, arr[0], ft_strlen(arr[0])) == 0)
		{
			free(temp->value);
			temp->value = NULL;
			temp->value = arr[1];
			return (0);
		}
		temp = temp->next;
	}
	return (-1);
}

void	add_new(t_tools *tools, char *str)
{
	t_env	*temp;
	t_env	*new;
	char	**temp_arr;

	new = NULL;
	temp_arr = ft_split(str, '=');
	if (!temp_arr)
		perror("malloc");
	if (key_exists(temp_arr, tools) == 0)
		return ;
	new = malloc(sizeof(t_env));
	new->key = ft_strdup(temp_arr[0]);
	new->value = ft_strdup(temp_arr[1]);
	new->next = NULL;
	free_array(temp_arr);
	temp = tools->env_list;
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
		printf("declare -x %s=\"%s\" \n", ptr->key, ptr->value);
		ptr = ptr->next;
	}
}

int	validate_arg(char *str)
{
	int	i;

	i = 1;
	if (ft_isalpha(str[0]) == 0)
	{
		printf("export: `%s': is not a valid identifier\n", str);
		return (-1);
	}
	return (0);
}

void	export_cmd(t_tools *tools)
{
	int i;

	i = 1;
	if (tools->split_rl[1] == NULL)
		output_export(tools->env_list);
	if (tools->split_rl[1])
	{
		while (tools->split_rl[i] != NULL)
		{
			if (validate_arg(tools->split_rl[i]) == 0)
				add_new(tools, tools->split_rl[i]);
			i++;
		}
	}
}