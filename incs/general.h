/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:03:56 by asalo             #+#    #+#             */
/*   Updated: 2024/08/09 16:07:17 by asalo            ###   ########.fr       */
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
# define UNKNOWN_CMD_ERR 10
# define TKN_SYNTAX_ERR 11
# define MEM_ERR 12
# define AMBIG_REDIR_ERR 13

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;

}					t_env;

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
