/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:46:30 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/14 14:12:43 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_rows(char *s, char c)
{
	int	count;
	int	i;
	int	countc;
	int	len;

	count = 1;
	i = 0;
	countc = 0;
	len = ft_strlen(s);
	while (*s)
	{
		if ((char)*s != c)
			break ;
		countc ++;
		s++;
	}
	if (countc == len)
		return (0);
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count ++;
		i ++;
	}
	return (count);
}

static	void	free_all(char **arr, int index)
{
	int	i;

	i = index;
	while (i >= 0)
	{
		free(arr[i]);
		i --;
	}
	free(arr);
}

static	int	count_len(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if ((char) *s == c)
			break ;
		count ++;
		s ++;
	}
	return (count);
}

static	void	fill(char *tab, char const *s, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		tab[i] = s[i];
		i ++;
	}
	tab[i] = '\0';
}

char	**ft_split(char const *s, char c)
{
	int		rows;
	int		i;
	char	**tab;

	rows = count_rows((char *)s, c);
	tab = (char **)malloc((rows + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = -1;
	while (i++ < rows - 1)
	{
		while ((char) *s == c)
			s ++;
		tab[i] = (char *)malloc((count_len(s, c) + 1) * sizeof(char));
		if (!tab[i])
		{
			free_all(tab, i);
			return (NULL);
		}
		fill(tab[i], (char *)s, count_len(s, c));
		s = s + ft_strlen(tab[i]);
	}
	tab[i++] = 0;
	return (tab);
}
