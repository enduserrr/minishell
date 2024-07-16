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
# include <stdio.h>				//printf
# include <unistd.h>			//execve
# include <sys/wait.h>			//for waitpid
# include "../libft/libft.h"	//libft
# include <readline/history.h>	//readline
# include <readline/readline.h>	//readline

//errors
# define MALLOC_ERROR 	"Error: malloc fails"

# define WELCOME 	"\n\nThis shell is created by two shitty students.\nUse it  at your own risk.\nIts use is not recommended to anyone\n\n\n"


typedef struct 		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;

}					t_env;

typedef struct 		s_hist
{
	char 			*cmd;
	struct s_hist 	*next;
} 					t_hist;

typedef struct s_tools
{
	char			*rl;
	char			**split_rl;

	char			*path;
	char			*prev_path;
	char			**paths;		//splitted PATH
	
	char			*valid_path;

	char			**envp;
	char			**new_envp;
	
	t_env			*env_list;
	t_hist			*history;

	int				exit_code;
	int				end;

	int 			ret_value;

}					t_tools;

void				run(char **envp);

// builtins
void				exit_cmd(t_tools *tools);
void				cd_cmd(t_tools *tools);
void				env_cmd(t_tools *tools);
void				echo_cmd(t_tools *tools);
void				pwd_cmd(t_tools *tools);
void				unset_cmd(t_tools *tools);
void				export_cmd(t_tools *tools);

// srcs
void				create_env_list(t_tools *tools);
void				free_env(t_tools *tools);
void				update_pwds(t_tools *tools, char *old_pwd);

// utils.c
void				free_array(char **arr);
void				free_all(t_tools *tools);
int					ft_arraylen(char **arr);

// history.c
void 				create_history(t_tools *tools);
void 				add_to_history(t_tools *tools);
void 				free_history(t_tools *tools);

// paths.c
void 				create_paths(t_tools *tools);
int					check_access(t_tools *tools);

// execution.c
void 				execute(t_tools *tools);
void 				execution(t_tools *tools);

#endif
