/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:10:41 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/14 11:11:14 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	cc;

	i = 0;
	cc = c;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)s + i);
		i++;
	}
	if (cc == 0)
		return ((char *)s + i);
	return (NULL);
}
