/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:06:10 by asalo             #+#    #+#             */
/*   Updated: 2024/07/24 18:51:05 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

static void	ft_free_path_list(char **path_list)
{
	int	i;

	i = 0;
	while (path_list[i])
	{
		free(path_list[i]);
		i++;
	}
	free(path_list);
}

static char *set_path(char *name)
{   
    char    **path_list;
    char	*path;
    size_t  p_len;
    int     i;

    path_list = ft_split(getenv("PATH"), ':');
	i = -1;
	while (path_list[++i])
	{
        if (path_list[i][0] == '\0')
            continue ;
        p_len = ft_strlen(path_list[i]);
        path = ft_calloc(p_len + 1 + ft_strlen(name) + 1, sizeof(char));
        if (!path)
            continue ;
        ft_memcpy(path, path_list[i], p_len);
        path[p_len] = '/';
        ft_memcpy(path + p_len + 1, name, ft_strlen(name));
        if (access(path, F_OK | X_OK) == 0)
            return (ft_free_path_list(path_list), path);
        free(path);
    }
    ft_free_path_list(path_list);
    return (NULL);
}

static char *get_path(char *name)
{
	struct stat	stats;

	if (!name[0] || !ft_strcmp(name, ".") || !ft_strcmp(name, ".."))
		exit(set_err(UNKNOWN_CMD_ERR, name));
	if (ft_strchr(name, '/') || !getenv("PATH"))
	{
		stat(name, &stats);
		if (S_ISDIR(stats.st_mode))
            return (NULL);
		return (ft_strdup(name));
	}
    return (set_path(name));
}

void    command_path(t_cmd *commands)
{
    while (commands)
    {
        commands->path = get_path(commands->av[0]);
        commands = commands->next;
    }
}