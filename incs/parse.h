/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:49:51 by asalo             #+#    #+#             */
/*   Updated: 2024/07/20 19:18:17 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft/incs/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>
# include <sys/stat.h>
# include <signal.h>

/**
 * @brief	Removal flag
 */
# define RMV -1
# define SUCCESS 0
# define FAIL 1

/**
 * @brief	Function return state
 */
typedef enum e_return_state
{
    RETURN_FAILURE,
    RETURN_SUCCESS
}   t_return_state;

typedef struct s_token
{
    char        	id;
    char        	*content;
    struct s_token	*next;
}   t_token;

typedef struct s_cmd
{
    char        *path;
    char        **av;
    t_token     *io_redir;
    int         fd_in;
    int         fd_out;
	void		*next;
}   t_cmd;

/**
 * @brief	Token identifiers in binary.
 *			Turha vaihtaa kun >> vaatii kaks inttia.
 *			Helpoi numeroida 0-11?
*/
typedef enum e_token_id
{
	WORD = 0b00000001,
	IN_FILE = 0b00000101,
	OUT_FILE = 0b00001001,
	COMMAND = 0b01000001,
	OPERATOR = 0b00000010,
	IN_REDIR = 0b00000110,/* < */
	OUT_REDIR = 0b00001010,/* > */
	HEREDOC = 0b00010010,/* << */
	HEREDOC_EOF = 0b00010001,/*17*/
	OUT_A_REDIR = 0b00100010,/* >> */
	OUT_A_FILE = 0b00100001,
	PIPE = 0b01000010/* | */
}   t_token_id;

/**
 * @brief	Error exit values. Change to exit 0/1. (static int in main to follow)
 */
typedef enum e_error_id
{
	ERRNO_ERR,
	UNSET_ERR = -1,
	MEM_ERR = 12,
	TKN_SYNTAX_ERR = 258,
	AMBIG_REDIR_ERR = -2,
	IS_DIR_ERR = 126,
	UNKNOWN_CMD_ERR = 127,
	NO_FILE_ERR = -3,
}			t_error_id;


// char	*get_path(char *name);
void    command_path(t_cmd *commands);

/*Token*/
t_token *ft_token(int *status, char *s);
t_token	*new_token(char *content);
t_token	*rm_token(t_token **top, t_token *remove);
size_t  unquoted_char(char *s, const char *chars, const char *quotes);
int		check_tokens(t_token *tokens);
char    split_at_operators(t_token *tokens);
void	free_tokens(t_token *tokens);

/*Parse*/
t_cmd   *ft_parse(int *status, t_token *tokens);
t_cmd	*alloc_cmd(t_token *tokens);
t_cmd	*command_table(t_token *tokens);
void    check_commands(t_token *tokens);
void 	free_commands(t_cmd *cmds);
void	put_command(t_cmd *commands);
char	expand_env(char **s, int status, char id);
char	ft_expand(int status, t_token **tokens);


/*Custom error*/
int		set_err(int err, char *context);

#endif
