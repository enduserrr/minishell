/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:22:12 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/14 11:23:02 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(sizeof(char) * len + 1);
	if (!(ptr))
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i ++;
	}
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = ('\0');
	return (ptr);
}
