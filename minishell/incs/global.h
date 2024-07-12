/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:58:16 by asalo             #+#    #+#             */
/*   Updated: 2024/07/12 15:43:02 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBA_H
# define GLOBAL_H

# include "../libft/incs/libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_outcome
{
    FAIL,
    SUCCESS
}   t_outcome;

typedef enum    e_errors
{
    ERRNO_ERR,
    UNSET_ERR = -1,
    MEM_ERR = 12,
    TKN_SYNTAX_ERR = 258,
    REDIR_ERR = -2,
    IS_DIR_ERR = 126,
    UNKNOWN_CMD_ERR = 127,
    NO_FILE_ERR = -3,
}   t_errors;

/**
 * @brief   Binary values for builtins (faast!!)
*/
typedef enum e_builtins
{
	B_NO = 0b00000000,/*0*/
	B_PARENT = 0b00000001,/*1*/
	B_EXIT = 0b00000011,/*3*/
	B_CD = 0b00000101,/*5*/
	B_EXPORT = 0b00001001,/*9*/
	B_UNSET = 0b00010001,/*17*/
	B_PWD = 0b00000010,/*2*/
	B_ECHO = 0b00000100,/*4*/
	B_ENV = 0b00001000,/*8*/
};

#endif