/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:05:54 by asalo             #+#    #+#             */
/*   Updated: 2024/07/20 14:41:44 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	size_t	i;

	i = ft_strlen(s1);
	// cpy = (char *)malloc(sizeof(char) * (i + 1));
	cpy = ft_calloc(i + 1, sizeof(char));
	if (!cpy)
		return (NULL);
	ft_memcpy(cpy, s1, i);
	cpy[i] = '\0';
	// ft_strlcpy(cpy, s1, ft_strlen(s1) + 1);
	return (cpy);
}
