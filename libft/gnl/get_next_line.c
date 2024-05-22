/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:48:48 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/29 15:52:10 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_until_nl(int fd, char *line, char *rest)
{
	int		bytes;
	char	buffer[BUFFER_SIZE + 1];

	while (ft_strchr(line, '\n') == NULL)
	{
		null_string(buffer);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (NULL);
		if (bytes < BUFFER_SIZE)
		{
			line = ft_strjoin_mod(line, line, buffer);
			if (!line)
				return (NULL);
			break ;
		}
		line = ft_strjoin_mod(line, line, buffer);
		if (!line)
			return (NULL);
	}
	if (bytes < BUFFER_SIZE)
		null_string(rest);
	return (line);
}

static char	*read_line(int fd, char *rest)
{
	char	*line;

	line = ft_strdup(rest);
	if (!line)
		return (NULL);
	null_string(rest);
	if (ft_strchr(line, '\n') == NULL)
		line = read_until_nl(fd, line, rest);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*fill_output(char *output, char *line, char *rest)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		output[i] = line[i];
		if (line[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	output[i] = '\0';
	if (ft_strlen(line) > i)
	{
		while (line[i])
			rest[j++] = line[i++];
	}
	rest[j] = '\0';
	free(line);
	return (output);
}

static char	*create_output(char *line, char *rest)
{
	char	*output;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		i++;
	output = malloc((i + 1) * sizeof(char));
	if (!output)
	{
		free(line);
		return (NULL);
	}
	output = fill_output(output, line, rest);
	if (!output)
	{
		free(output);
		return (NULL);
	}
	return (output);
}

char	*get_next_line(int fd)
{
	static char	rest[BUFFER_SIZE + 1];
	char		*line;
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		null_string(rest);
		return (NULL);
	}
	line = read_line(fd, rest);
	if (!line)
		return (NULL);
	output = create_output(line, rest);
	if (!output)
	{
		free(output);
		return (NULL);
	}
	return (output);
}
