/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:38:32 by asalo             #+#    #+#             */
/*   Updated: 2024/03/19 21:13:34 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Dynamically allocate memory for 'count' number of objects
 * 			of a specified 'size', initializing the allocated memory to zero. 
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (count && size && count > (UINT_MAX / size))
		return (NULL);
	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, count * size);
	return (mem);
}
