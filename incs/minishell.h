/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:11:52 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/29 10:02:21 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* LIBS */
# include "libft/incs/libft.h"
# include "builtins.h"
# include "parse.h"
// # include ""

// # include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
// # include <signal.h>
# include <stdio.h>
// # include <stdlib.h>
// # include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define MALLOC_ERROR "Error: malloc fails"
# define WLCM "\n\nThis (s)hell emulator was created by two shitty students.\
					\nUse it  at your own risk.\n\n"


typedef struct s_hist /*might be useless?*/
{
	char			*cmd;
	struct s_hist	*next;
}			t_hist;

/**
 * @brief	List description:
 */
typedef struct s_data
{
	t_cmd	*cmds;
	char	*path;
	char	*prev_path;
	char	**paths;

	char	**envp;
	char	**new_envp;
	char	unset_path;
	t_env	*env_list;
	t_hist	*history;
	pid_t	*pid_arr;

	int		pipe_amount;

	int		exit_code;
}			t_data;

/* BUILTIN */
void		exit_cmd(t_data *data);
void		cd_cmd(t_data *data);
void		env_cmd(t_data *data);
void		echo_cmd(t_data *data);
void		pwd_cmd(t_data *data);
void		unset_cmd(t_data *tools);
void		export_cmd(t_data *data);
void		update_pwds(t_data *tools, char *old_pwd);

/* FREE */
void		free_env(t_data *data);
void		free_array(char **arr);

/* SRC */
void		create_env_list(t_data *data);

/* UTILS */
void		free_array(char **arr);
void		free_all(t_data *tools);
int			ft_arraylen(char **arr);

/* PATHS */
void		create_paths(t_data *data);
void		delete_paths(t_data *data);

/* EXECUTION */
int			is_builtin(t_data *data);
void		execution(t_data *tools);
void		execute_cmd(t_data *tools, int i);
// void				run(char **envp);

/* PIPES */
int			pipes_in_prompt(t_data *tools);
void		create_pids(t_data *tools);
void		next_pipe(t_data *data, int *prev_fd, int *fd, int i);

/* REDIRECTIONS */
int			check_redir(t_data *data, int i);

/* HISTORY */
// void 				create_history(t_data *tools);
// void 				add_to_history(t_data *tools);
// void 				free_history(t_data *tools);

#endif
