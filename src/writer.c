/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:49:21 by asalo             #+#    #+#             */
/*   Updated: 2024/08/02 12:04:24 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/general.h"

void write_fd(int fd, const char *color, const char *text)
{
    write(fd, color, ft_strlen(color));
    write(fd, text, ft_strlen(text));
    write(fd, RESET, ft_strlen(RESET));
}
