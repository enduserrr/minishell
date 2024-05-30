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

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>


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

void		run(char **envp);

// builtins
void		exit_cmd(t_tools *tools);
void		cd_cmd(t_tools *tools);
void		env_cmd(t_tools *tools);
void		echo_cmd(t_tools *tools);
void		pwd_cmd(t_tools *tools);
void		unset_cmd(t_tools *tools);
void		export_cmd(t_tools *tools);

//srcs
void   		create_env_list(t_tools *tools);
void    	print_env(t_env *env);
void 		free_env(t_tools *tools);
void    	print_env(t_env *env);
void   		update_pwds(t_tools *tools, char *old_pwd);

// utils.c
void		free_array(char **arr);
void		free_all(t_tools *tools);
int     	ft_arraylen(char **arr);

#endif
