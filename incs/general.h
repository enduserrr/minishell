/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:03:56 by asalo             #+#    #+#             */
/*   Updated: 2024/08/08 18:00:30 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include "libft/incs/libft.h"
# include <errno.h> /*custom_error*/
# include <fcntl.h> /*open*/
# include <readline/history.h> /*readline*/
# include <readline/readline.h> /*readline*/
# include <signal.h> /*signals*/
# include <stdio.h> /*printf*/
# include <sys/ioctl.h> /*heredoc signal disrupt*/
# include <sys/stat.h> /*expand*/
# include <sys/wait.h> /*for waitpid*/
# include <termios.h> /*Terminal configuration*/

# define RED "\033[1;91m"
# define GREEN "\033[1;92m"
# define YELLOW "\033[1;93m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

# define WLCM "\n\nThis (s)hell emulator was created by two shitty students.\
							\nUse it  at your own risk.\n\n"

// # define ERRNO_ERR 0
// # define UNSET_ERR -1
# define MEM_ERR 12
# define TKN_SYNTAX_ERR 258
# define AMBIG_REDIR_ERR -2
# define IS_DIR_ERR 126
# define UNKNOWN_CMD_ERR 127
// # define NO_FILE_ERR -3

typedef struct s_exit
{
	int	state;
}		t_exit;

/* CUSTOM ERROR OUTPUT */
int		set_err(int err, char *context, t_exit *state);

/* SIGNALS */
void	sig_handle_heredoc(int sig);
void	signal_handler(int sig);
void	sig_handle_child(int sig);
int		*signal_trigger(void);
void	sig_handle_nl(int sig);

void	write_fd(int fd, const char *color, const char *text);

#endif
