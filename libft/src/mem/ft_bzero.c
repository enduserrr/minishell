/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:16:24 by asalo             #+#    #+#             */
/*   Updated: 2024/03/19 21:14:03 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Set's the specified block of memory to zero.
*/
void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char *)s++ = 0;
}
