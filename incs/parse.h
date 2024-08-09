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

# include "general.h"

# define REMOVE -4

typedef struct s_token
{
	char			id;
	char			*content;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			*path;
	char			**av;
	t_token			*io_redir;
	int				fd_in;
	int				fd_out;
	void			*next;
}					t_cmd;

/**
 * @brief	Token identifiers in binary.
 */
typedef enum e_token_id
{
	WORD = 0b00000001,
	IN_FILE = 0b00000101,
	OUT_FILE = 0b00001001,
	COMMAND = 0b01000001,
	OPERATOR = 0b00000010,
	IN_REDIR = 0b00000110,
	OUT_REDIR = 0b00001010,
	HEREDOC = 0b00010010,
	HEREDOC_EOF = 0b00010001,
	OUT_A_REDIR = 0b00100010,
	OUT_A_FILE = 0b00100001,
	PIPE = 0b01000010
}	t_token_id;

/*Token*/
t_token				*ft_token(t_exit *state, char *s);
t_token				*new_token(char *content, t_exit *state);
t_token				*rm_token(t_token **top, t_token *remove);
size_t				unquoted_char(char *s, const char *chars,
						const char *quotes);
int					check_tokens(t_token *tokens, t_exit *state);
char				split_at_operators(t_token *tokens, t_exit *state);
void				free_tokens(t_token *tokens);

/*Parse*/
t_cmd				*ft_parse(t_exit *state, t_token *tokens, t_env *env);
t_cmd				*alloc_cmd(t_token *tokens);
t_cmd				*command_table(t_token *tokens, t_exit *state);
void				check_commands(t_token *tokens);
void				free_commands(t_cmd *cmds);
char				expand_env(char **s, t_exit *state, char id, \
						t_env *env_list);
char				ft_expand(t_exit *state, t_token **tokens, t_env *env);
char				*find_env(char *env, t_env *env_list);

/*void				put_command(t_cmd *commands);*/
#endif
