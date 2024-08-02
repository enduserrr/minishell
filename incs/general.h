/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   # include "general.h"                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:03:56 by asalo             #+#    #+#             */
/*   Updated: 2024/08/02 11:50:47 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include "libft/incs/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>				/*for waitpid*/
# include <unistd.h>				/*execve*/
# include <readline/history.h>		/*readline*/
# include <readline/readline.h>		/*readline*/
# include <fcntl.h>					/*open*/
# include <term.h>					/*tgetent etc*/

# define RED		"\033[1;91m"
# define GREEN		"\033[1;92m"
# define YELLOW		"\033[1;93m"
# define WHITE		"\033[0;37m"
# define RESET			"\033[0m"

# define WLCM 			"\n\nThis (s)hell emulator was created by two shitty students.\
							\nUse it  at your own risk.\n\n"

# define	ERRNO_ERR 0
# define	UNSET_ERR -1
# define	MEM_ERR 12
# define	TKN_SYNTAX_ERR 258
# define	AMBIG_REDIR_ERR -2
# define	IS_DIR_ERR 126
# define	UNKNOWN_CMD_ERR 127
# define	NO_FILE_ERR -3

typedef struct s_exit
{
	int	state;
}	t_exit;

/* CUSTOM ERROR OUTPUT */
int		set_err(int err, char *context, t_exit *state);

/* SIGNAL */
void	sig_handle_heredoc(int sig);
void	signal_handler(int sig);
void	sig_handle_child(int sig);
int		*signal_trigger(void);
void	sig_handle_nl(int sig);

/* WRITE WITH COLORS */
// void	write_red(int fd, const char *text);
// void	write_green(int fd, const char *text);
// void	write_white(int fd, const char *text);
// void	std_write(int fd, const char *text);
void write_fd(int fd, const char *color, const char *text);

#endif
