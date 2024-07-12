/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:49:16 by asalo             #+#    #+#             */
/*   Updated: 2024/07/12 12:57:35 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <signal.h>

# include "tokenize.h"

# define RMV -1

typedef struct s_cmd
{
    char    *path;
    char    **av;
    t_tokens    io_red;
    int         fd_in;
    int         fd_out;
    char        builtin;
}   t_cmd;

#endif