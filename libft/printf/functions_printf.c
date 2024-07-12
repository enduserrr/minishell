/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:02:32 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/23 12:19:07 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_negative(int n)
{
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	return (write(1, "-", 1));
}

int	ft_puthexa(unsigned int nb, int count, char c)
{
	char	s[40];
	int		i;

	i = 0;
	if (nb == 0)
		s[i++] = '0';
	while (nb > 0)
	{
		s[i] = nb % 16;
		if (s[i] >= 10)
		{
			if (c == 'X')
				s[i] = s[i] + 'A' - 10;
			else
				s[i] = s[i] + 'a' - 10;
		}
		else
			s[i] = s[i] + '0';
		nb = nb / 16;
		i ++;
	}
	count = ft_string(s, i, count);
	if (count < 0)
		return (-1);
	return (count);
}

int	ft_pointer(unsigned long nb, int count)
{
	char	s[40];
	int		i;

	i = 0;
	if (nb == 0)
		s[i++] = '0';
	while (nb > 0)
	{
		s[i] = nb % 16;
		if (s[i] >= 10)
			s[i] = s[i] + 'a' - 10;
		else
			s[i] = s[i] + '0';
		nb = nb / 16;
		i ++;
	}
	if (write(1, "0x", 2) < 0)
		return (-1);
	count = ft_string(s, i, count);
	if (count < 0)
		return (-1);
	return (count + 2);
}

int	ft_unsigned_int(unsigned int n, int count)
{
	char	s[20];
	int		i;

	i = 0;
	if (n == 0)
	{
		if (write(1, "0", 1) < 0)
			return (-1);
		count ++;
	}
	while (n > 0)
	{
		s[i++] = (n % 10) + '0';
		n = n / 10;
	}
	while (--i >= 0)
	{
		if (write(1, &s[i], 1) < 0)
			return (-1);
		count ++;
	}
	return (count);
}

int	ft_string(char *s, int i, int count)
{
	if ((char *)s == NULL)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		return (count + 6);
	}
	if (i == 0)
	{
		while (*s)
		{
			if (write(1, &*s, 1) < 0)
				return (-1);
			count ++;
			s ++;
		}
		return (count);
	}
	while (--i >= 0)
	{
		if (write(1, &s[i], 1) < 0)
			return (-1);
		count ++;
	}
	return (count);
}
