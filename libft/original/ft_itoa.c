/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:01:33 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/14 10:01:42 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	nsize(int n)
{
	unsigned int	i;
	unsigned int	nb;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i ++;
		nb = n * -1;
	}
	else
		nb = n;
	while (nb > 0)
	{
		nb = nb / 10;
		i ++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	length;
	unsigned int	nb;
	char			*ptr;

	length = nsize(n);
	ptr = malloc(sizeof(char) * length + 1);
	if (!ptr)
		return (NULL);
	ptr[length] = '\0';
	if (n < 0)
	{
		ptr[0] = '-';
		nb = n * -1;
	}
	else
		nb = n;
	if (nb == 0)
		ptr[--length] = '0';
	while (nb > 0)
	{
		ptr[--length] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (ptr);
}
