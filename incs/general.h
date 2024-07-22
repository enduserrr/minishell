/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:06:15 by asalo             #+#    #+#             */
/*   Updated: 2024/07/22 09:33:10 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

/**
 * @brief   In general.h signal handling & error handling.
*/

# include "libft/incs/libft.h"
# include <signal.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <term.h>

/* GLOBAL VAR FOR SIGNAL HANDLING */
volatile sig_atomic_t   g_sig;

#endif
