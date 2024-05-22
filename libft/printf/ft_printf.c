/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:20:08 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/22 13:34:37 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int	ft_putnbr(int n, int count)
{
	char	s[20];
	int		i;

	if (n < 0)
	{
		i = ft_negative(n);
		if (i < 0)
			return (-1);
		if (i == 11)
			return (count + i);
		n = n * -1;
		count ++;
	}
	i = 0;
	if (n == 0)
		s[i++] = '0';
	while (n > 0)
	{
		s[i++] = (n % 10) + '0';
		n = n / 10;
	}
	count = ft_string(s, i, count);
	if (count < 0)
		return (-1);
	return (count);
}

static	int	ft_character(char c, int count)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	count ++;
	return (count);
}

static	int	next(const char *s, va_list args, int count, int i)
{
	i ++;
	if (s[i] == '%')
	{
		if (write(1, &s[i], 1) < 0)
			return (-1);
		count ++;
	}
	else if (s[i] == 'd' || s[i] == 'i')
		count = ft_putnbr(va_arg(args, int), count);
	else if (s[i] == 's')
		count = ft_string(va_arg(args, char *), 0, count);
	else if (s[i] == 'c')
		count = ft_character(va_arg(args, unsigned int), count);
	else if (s[i] == 'u')
		count = ft_unsigned_int(va_arg(args, int), count);
	else if (s[i] == 'p')
		count = ft_pointer((unsigned long long)va_arg(args, void *), count);
	else if (s[i] == 'x' || s[i] == 'X')
		count = ft_puthexa((unsigned int)va_arg(args, void *), count, s[i]);
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
			count = next(s, args, count++, i ++);
		else
			count = ft_character(s[i], count);
		if (count < 0)
		{
			va_end(args);
			return (count);
		}
		i ++;
	}
	va_end(args);
	return (count);
}
