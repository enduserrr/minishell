/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:11:52 by eleppala          #+#    #+#             */
/*   Updated: 2024/06/04 08:27:56 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incs/libft.h"
# include <stdio.h>
# include <signal.h>
// # include <unistd.h>/*already included in libft.h*/
# include <reads/history.h>
# include <reads/reads.h>

/**
 * @brief	Global variable for signals.
*/
extern int	g_signal;

/*tkn types*/
# define EMPTY 0
# define CMD 1
# define INPUT 5
# define PIPE 6
# define APPEND 4
# define ARG 2
# define TRUNC 3
# define END 7

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
} t_bool;

typedef struct s_list
{
	t_list	*tkn;
	t_list	*env;
	t_list	*tools;
	t_list	*sig;
	t_list	*exps;
}			t_list;

typedef struct	s_tkn
{
	char			*str;
	int				type;
	struct s_tkn	*prev;
	struct s_tkn	*next;
}			t_tkn;

typedef struct	s_shell
{
	t_tkn			*start;
	t_env			*env;
	int				pid;
	int				last;
	int				exit;
	int				no_exec;
}			t_shell;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env 	*next;

}			t_env;

typedef struct s_tools
{
	char		*rl;
	char		**split_rl;
	
	char		*path;
	char		*prev_path;
	char		**paths;

	char		**envp;
	char		**new_envp;
	t_env 		*env_list;
	
	int			exit_code;
	int			end;

}			t_tools;

typedef struct	s_exps
{
	char			*new_arg;
	int				i;
	int				j;
}			t_exps;

void		run(char **envp);

/*builtins*/
void		exit_cmd(t_tools *tools);
void		cd_cmd(t_tools *tools);
void		env_cmd(t_tools *tools);
void		echo_cmd(t_tools *tools);
void		pwd_cmd(t_tools *tools);
void		unset_cmd(t_tools *tools);
void		export_cmd(t_tools *tools);

/*parse*/
t_tkn		*get_tkns(char *s);
t_tkn		*next_tkn(char *s, int *i);
int			next_alloc(char *s, int *i);
void		handle_args(t_shell *shell);
void		arg_type(t_tkn *token, int sep);

void		*clear_ptr(void *ptr);
void		skip_if(const char *str, t_bool *i);
t_tkn		*next_sep(t_tkn *token, t_bool skip);
t_tkn		*prev_sep(t_tkn *token, t_bool skip);
t_tkn		*next_run(t_tkn *token, t_bool skip);

/*srcs*/
void		create_env_list(t_tools *tools);
void		print_env(t_env *env);
void 		free_env(t_tools *tools);
void		print_env(t_env *env);
void		update_pwds(t_tools *tools, char *old_pwd);

/*utils.c*/
void		free_array(char **arr);
void		free_all(t_tools *tools);
int			ft_arraylen(char **arr);

#endif
