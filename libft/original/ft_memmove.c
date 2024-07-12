/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:50:13 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/14 10:03:08 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*ddst;
	char	*ssrc;
	size_t	i;

	i = 0;
	ddst = (char *)dst;
	ssrc = (char *)src;
	if (dst == 0 && src == 0)
		return (dst);
	if (ddst > ssrc)
	{
		while (len-- > 0)
			ddst[len] = ssrc[len];
	}
	else
	{
		while (i < len)
		{
			ddst[i] = ssrc[i];
			i ++;
		}
	}
	return (dst);
}
