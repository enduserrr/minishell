/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:48:36 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/07 18:48:38 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_arraylen(char **arr)
{
	int len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}