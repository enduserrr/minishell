/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:49:51 by asalo             #+#    #+#             */
/*   Updated: 2024/07/18 10:48:21 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

/*# include "minishell.h"*/
# include "libft/incs/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>
# include <sys/stat.h>

/*'remove' flag/verbose*/
# define RMV -1

typedef enum e_return_state
{
    RETURN_FAILURE,
    RETURN_SUCCESS
}   t_return_state;

/**
 * @brief	Enum underlying type usually signed int.
*/
typedef enum    e_errors
{
    ERRNO_ERR,
    UNSET_ERR = -1,
    MEM_ERR = 12,
    TKN_SYNTAX_ERR = 258,
    AMBIG_REDIR_ERR = -2,
    IS_DIR_ERR = 126,
    UNKNOWN_CMD_ERR = 127,
    NO_FILE_ERR = -3,
}   t_errors;

/**
 * @brief	Token identifiers in binary.
*/
typedef enum e_tkn_id /*Re-organice*/
{
	WORD = 0b00000001,/*1*/
	IN_FILE = 0b00000101,/*5*/
	OUT_FILE = 0b00001001,/*9*/
	COMMAND = 0b01000001,/**/
	OPERATOR = 0b00000010,/**/
	IN_REDIR = 0b00000110,/* < */
	OUT_REDIR = 0b00001010,/* > */
	HEREDOC = 0b00010010,/* << */
	HEREDOC_EOF = 0b00010001,/*17*/
	OUT_A_REDIR = 0b00100010,/* >> */
	OUT_A_FILE = 0b00100001,/**/
	PIPE = 0b01000010/* | */
}   t_tkn_id;

typedef struct s_token
{
    char        	id;
    char        	*content;
    struct s_token	*next;
}   t_token;

/**
 * @brief   Builtin identifiers in binary.
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
}	t_builtins;

typedef struct s_cmd
{
    char        *path;
    char        **av;
    t_token     *io_redir;
    int         fd_in;
    int         fd_out;
    char        builtin;
	void		*next;
}   t_cmd;

/* Tokens */
t_token *tokenizer(int *status, char *s);
t_token	*new_token(char *content);
t_token *put_tkn(t_token *tokens, const char *title);
size_t  unquoted_char(char *s, const char *chars, const char *quotes);
int		check_tokens(t_token *tokens);
char    split_at_operators(t_token *tokens);
void	free_tokens(t_token *tokens);

/* Parsing */
t_cmd   *parse(int *status, t_token *tokens);
t_cmd	*alloc_cmd(t_token *tokens);
t_cmd	*create_cmd_table(t_token *tokens);
void    eval_commands(t_token *tokens);
void 	free_cmds(t_cmd *cmds);
void	put_cmd(t_cmd *cmds);
char	ft_expand(char **s, int status, char id);
char	expand_tkns(int status, t_token **tokens);

/* Utils */
int		parsing_err(int err, char *context);
ssize_t set_char(char *s, char c, ssize_t i);
char	*ft_strcpy(char *dst, const char *src);

#endif