/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:40:47 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/14 11:40:52 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	cc;

	i = 0;
	cc = c;
	while (s[i])
		i ++;
	while (i >= 0)
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i --;
	}
	return (NULL);
}
