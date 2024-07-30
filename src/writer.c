/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:49:21 by asalo             #+#    #+#             */
/*   Updated: 2024/07/30 10:07:43 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void    bold_red(int fd, const char *text)
{
    write(fd, BOLD_RED, ft_strlen(BOLD_RED));
    write(fd, text, ft_strlen(text));
    write(fd, RESET, ft_strlen(RESET));
}

void    bold_green(int fd, const char *text)
{
    write(fd, BOLD_GREEN, ft_strlen(BOLD_GREEN));
    write(fd, text, ft_strlen(text));
    write(fd, RESET, ft_strlen(RESET));
}

void    bold_white(int fd, const char *text)
{
    write(fd, BOLD_WHITE, ft_strlen(BOLD_WHITE));
    write(fd, text, ft_strlen(text));
    write(fd, RESET, ft_strlen(RESET));
}

void    std_write(int fd, const char *text)
{
    write(fd, text, ft_strlen(text));
}
