/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:11:52 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/02 11:51:14 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* LIBS */
# include "general.h"
# include "builtins.h"
# include "parse.h"

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
	pid_t	*pid_arr;

	int		pipe_amount;

	t_exit	*exit_code;
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
int			check_out(t_cmd *temp, int fd);
int    		heredoc_handler(t_cmd *temp, char *delimiter, int fd_out);

/* FREE */
void		free_all(t_data *tools);
void		free_env(t_data *data);
void		free_array(char **arr);

/* SRC */
void		create_env_list(t_data *data);

/* UTILS */
int			ft_arraylen(char **arr);

/* PATHS */
void		create_paths(t_data *data);
void		delete_paths(t_data *data);

/* EXECUTION */
int			is_builtin(t_data *data);
void		execution(t_data *tools);
void		execute_cmd(t_data *tools, int i);

/* PIPES */
int			pipes_in_prompt(t_data *tools);
void		create_pids(t_data *tools);
void		next_pipe(t_data *data, int *prev_fd, int *fd, int i);

/* REDIRECTIONS */
int			check_redir(t_data *data, int i);


#endif
