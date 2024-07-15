/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:11:52 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/15 12:39:23 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include "../libft/incs/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>
# include <sys/stat.h>

# define MALLOC_ERROR "Error: malloc fails"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;

}					t_env;

typedef struct s_tools
{
	char			*rl;
	char			**split_rl;

	char			*path;
	char			*prev_path;
	char			**paths;

	char			**envp;
	char			**new_envp;
	t_env			*env_list;

	int				exit_code;
	int				end;

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

#endif
