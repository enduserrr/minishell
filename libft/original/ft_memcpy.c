/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:07:20 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/14 12:07:44 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*destination;
	char	*source;

	if (src == dst || n == 0)
		return (dst);
	i = 0;
	destination = dst;
	source = (char *) src;
	while (i < n)
	{
		destination[i] = source[i];
		i ++;
	}
	return (dst);
}
