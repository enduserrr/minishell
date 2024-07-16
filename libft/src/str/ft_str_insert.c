/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:19:26 by asalo             #+#    #+#             */
/*   Updated: 2024/07/16 17:27:41 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

/**
 * @brief   Modify to add string 'c' into string 's' starting from 'start'.
 *          Returns (void *)0 upon succes and (void *)1 upon failure.
 *
 *          Copy the part of 'ret' before 'start'.
 *          Insert 'len' nb of chars from 'insert'.
 *          Copy the re of ret after 'start'.
 *          Copy the modified str back to 'ret'.
 *          Free temp.
 */
void	*ft_str_insert(char *ret, const char *insert, size_t start, size_t len)
{
	size_t	new_len;
	char	*temp;

	if (!ret || !insert)
		return ((void *)1);
	if (start > ft_strlen(ret))
		return ((void *)1);
	if (len > ft_strlen(insert))
		len = ft_strlen(insert);
	new_len = ft_strlen(ret) + len;
	temp = (char *)malloc(new_len + 1);
	if (!temp)
		return ((void *)1);
	ft_memcpy(temp, ret, start);
	ft_memcpy(&temp[start], insert, len);
	ft_memcpy(&temp[start + len], &ret[start], ft_strlen(ret) - start + 1);
	ft_memcpy(ret, temp, new_len);
	free(temp);
	return ((void *)0);
}
