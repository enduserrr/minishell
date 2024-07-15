/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:44:28 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/14 12:00:09 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_check(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i ++;
	}
	return (0);
}

static	char	*ft_start(char *s1, char *set)
{
	while (s1)
	{
		if (ft_check((char) *s1, (char *)set) == 0)
			break ;
		s1 ++;
	}
	return (s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		i;
	char	*ptr;

	i = 0;
	s1 = ft_start((char *)s1, (char *)set);
	len = ft_strlen(s1);
	while (len > 0)
	{
		if (ft_check(s1[len - 1], (char *)set) == 0)
			break ;
		len --;
	}
	ptr = malloc(len * sizeof(char) + 1);
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s1[i];
		i ++;
	}
	ptr[i] = '\0';
	return (ptr);
}
