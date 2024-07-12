/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:24:51 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/14 11:25:16 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(dst) + ft_strlen(src);
	i = 0;
	if (dstsize == 0 || ft_strlen(dst) >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (*dst)
	{
		dst ++;
		i ++;
	}
	while (*src && i < (dstsize - 1))
	{
		*dst ++ = *src ++;
		i ++;
	}
	*dst = '\0';
	return (len);
}
