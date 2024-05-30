/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:15:26 by asalo             #+#    #+#             */
/*   Updated: 2023/12/05 11:50:13 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*newstr;

	i = 0;
	if (!s || !f)
		return (0);
	len = ft_strlen(s);
	newstr = (char *)malloc(sizeof(char) * (len + 1));
	if (!newstr)
		return (0);
	while (i < len)
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	newstr[i] = 0;
	return (newstr);
}
