/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:49:51 by asalo             #+#    #+#             */
/*   Updated: 2024/07/15 13:39:07 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "minishell.h"

/*Remove flag*/
# define RMV -1

# define EXIT_SUCCESS 1
# define EXIT_FAILURE 0


typedef enum e_return_state
{
    RETURN_FAILURE,
    RETURN_SUCCESS
}   t_return_state;

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
 * @brief	Token identifiers in binary. (Fast!!)
*/
enum e_tkn_id
{
	WORD = 0b00000001,/*1*/
	IN_FILE = 0b00000101,/*5*/
	OUT_FILE = 0b00001001,/*9*/
	HEREDOC_EOF = 0b00010001,/*17*/
	OUT_A_FILE = 0b00100001,/*33*/
	COMMAND = 0b01000001,/*65*/
	OPERATOR = 0b00000010,/*2*/
	IN_REDIR = 0b00000110,/*6*/
	OUT_REDIR = 0b00001010,/*10*/
	HEREDOC = 0b00010010,/*18*/
	OUT_A_REDIR = 0b00100010,/*34*/
	PIPE = 0b01000010/*66*/
}   t_tkn_id;

/**
 * @brief   Nuiltin identifiers in binary.(Still fast!!)
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

typedef struct s_token
{
    char        	id;/*Should this be unsigned char for binary values*/
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
    char        builtin;
	struct s_cmds	*next;
}   t_cmd;

t_token *tokenizer(int *status, char *s);
int		eval_tokens(t_token *tokens);
char    split_at_operators(t_token *tokens);

/* Utils */
t_token	*new_token(char *content);
void	free_tokens(t_token *tokens);
size_t  unquoted_char(char *s, const char *chars, const char *quotes);
t_token *put_tkn(t_token *tokens, const char *title);


#endif