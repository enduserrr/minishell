/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:37:05 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/14 09:57:54 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	csize;

	if (size == 0 || count == 0)
		return (malloc(0));
	//if (count > SIZE_MAX / size)
		//return (NULL);
	csize = count * size;
	if (csize >= 4611686014132420609)
		return (NULL);
	ptr = malloc(csize);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, csize);
	return (ptr);
}
