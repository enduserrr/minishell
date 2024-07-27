/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:11:52 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/07 14:11:54 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// libraries
# include <stdio.h>					//printf
# include <unistd.h>				//execve
# include <sys/wait.h>				//for waitpid
# include <readline/history.h>		//readline
# include <readline/readline.h>		//readline
# include <fcntl.h>					//open

// 
# include "libft/incs/libft.h"		//libft
# include "parse.h"
# include "builtins.h"

//errors
# define MALLOC_ERROR 	"Error: malloc fails"

# define WELCOME 	"\n\nThis shell is created by two shitty students.\nUse it  at your own risk.\nIts use is not recommended to anyone\n\n\n"

typedef struct 		s_hist
{
	char 			*cmd;
	struct s_hist 	*next;
} 					t_hist;


typedef struct 		s_data
{
	t_cmd			*cmds;
	char			*path;
	char			*prev_path;
	char			**paths;		//splitted PATH
	
	char			**envp;
	char			**new_envp;
	char			unset_path; 	//0 path ok, 1 path has been unsetted
	
	t_env			*env_list;
	t_hist			*history;
	pid_t			*pid_arr;

	int				pipe_amount;

	int				exit_code;
}					t_data;

//void				run(char **envp);

// builtins
void				exit_cmd(t_data *data);
void				cd_cmd(t_data *data);
void				env_cmd(t_data *data);
void				echo_cmd(t_data *data);
void				pwd_cmd(t_data *data);
void				unset_cmd(t_data *tools);
void				export_cmd(t_data *data);
void				update_pwds(t_data *tools, char *old_pwd);

//free.c
void				free_env(t_data *data);
void				free_array(char **arr);

// srcs
void				create_env_list(t_data *data);

// utils.c
void				free_array(char **arr);
void				free_all(t_data *tools);
int					ft_arraylen(char **arr);


// history.c
void 				create_history(t_data *tools);
void 				add_to_history(t_data *tools);
void 				free_history(t_data *tools);

// paths.c
void 				create_paths(t_data *data);
void 				delete_paths(t_data *data);

// execution.c
int					is_builtin(t_data *data);
void 				execution(t_data *tools);
void 				execute_cmd(t_data *tools, int i);

// pipes.c
int					pipes_in_prompt(t_data *tools);
void 				create_pids(t_data *tools);


//redir
int 				check_redir(t_data *data, int i);

#endif
