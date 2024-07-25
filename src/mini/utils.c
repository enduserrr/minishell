/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:48:36 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/25 16:24:01 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

ssize_t	ft_strrchr_index(const char *s, int c)
{
	ssize_t	i;

	i = ft_strlen(s);
	if ((char)c == '\0')
		return (i);
	while (--i >= 0)
		if (s[i] == (char)c)
			return (i);
	return (-1);
}

ssize_t	ft_strchr_index(const char *s, int c)
{
	ssize_t	i;

	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return (i);
	if ((char)c == '\0')
		return (i);
	return (-1);
}

int	ft_arraylen(char **arr)
{
	int len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}