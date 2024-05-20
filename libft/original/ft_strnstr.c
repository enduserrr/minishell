/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:42:34 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/14 11:42:43 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;

	if ((haystack == NULL || needle == NULL) && len == 0)
		return (NULL);
	nlen = ft_strlen(needle);
	if (nlen == 0)
		return ((char *)haystack);
	while (*haystack && len >= nlen)
	{
		if (*haystack == *needle && ft_strncmp(haystack, needle, nlen) == 0)
			return ((char *)haystack);
		haystack ++;
		len --;
	}
	return (NULL);
}
