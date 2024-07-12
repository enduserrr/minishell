/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:23:36 by asalo             #+#    #+#             */
/*   Updated: 2023/12/05 11:50:19 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *main_s, const char *sub_s, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!main_s && !len)
		return (0);
	if (sub_s[0] == '\0' || sub_s == main_s)
		return ((char *)main_s);
	while (main_s[i] != '\0')
	{
		j = 0;
		while (main_s[i + j] == sub_s[j] && (i + j) < len)
		{
			if (main_s[i + j] == '\0' && sub_s[j] == '\0')
				return ((char *)&main_s[i]);
			j++;
		}
		if (sub_s[j] == '\0')
			return ((char *)(main_s + i));
		i++;
	}
	return (0);
}
