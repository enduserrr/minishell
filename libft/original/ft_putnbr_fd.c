/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:17:44 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/14 10:17:51 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	str[15];
	int		i;

	i = 0;
	if (n == 0)
		write(fd, "0", 1);
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(fd, "-2147483648", 11);
			return ;
		}
		write(fd, "-", 1);
		n = n * -1;
	}
	while (n > 0)
	{
		str[i++] = (n % 10) + '0';
		n = n / 10;
	}
	while (i > 0)
		write(fd, &str[--i], 1);
}
