/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:29:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/20 18:41:43 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*sub;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	sub = ft_calloc(len + 1, sizeof(char));
	if (!sub)
		return (NULL);
	// ft_memcpy(sub, s + start, len);
	// size = ft_strlen(sub) + 1;
	// sub[size] = '\0';
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
