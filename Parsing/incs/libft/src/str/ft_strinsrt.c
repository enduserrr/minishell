/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsrt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:19:26 by asalo             #+#    #+#             */
/*   Updated: 2024/07/20 12:45:33 by asalo            ###   ########.fr       */
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
void	*ft_strinsrt(char **ret, const char *insert, size_t start, size_t len)
{
	size_t	new_len;
	size_t	ret_len;
	char	*temp;

	if (!ret)
		return ((void *)1);
	if (!insert)
		insert = "";
	ret_len = ft_strlen(*ret);
	if (start > ret_len)
		return ((void *)1);
	if (len > ft_strlen(insert))
		len = ft_strlen(insert);
	new_len = ret_len + len;
	// temp = (char *)malloc(new_len + 1);
	temp = ft_calloc(new_len + 1, sizeof(char));
	if (!temp)
		return ((void *)1);
	ft_memcpy(temp, *ret, start);
	ft_memcpy(&temp[start], insert, len);
	ft_memcpy(&temp[start + len], &(*ret)[start], ret_len - start + 1);
	free(*ret);
	*ret = temp;
	return ((void *)0);
}
