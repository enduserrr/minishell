/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:49:51 by asalo             #+#    #+#             */
/*   Updated: 2024/07/12 15:40:19 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "global.h"

/**
 * @brief	Token identifiers in binary values.
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

typedef struct s_token
{
    char        	id;/*Should this be unsigned char for binary values*/
    char        	*content;
    struct s_token	*next;
}   t_token;

t_token *tokenizer(int *status, char *s);
int		eval_tokens(t_token *tokens);
char    split_at_operators(t_token *tokens);

/* Utils */
t_token	*new_token(char *content);
void	tokens_free(t_token *tokens);
size_t  unquoted_char(char *s, const char *chars, const char *quotes);
t_token *put_tkn(t_token *tokens, const char *title);


#endif