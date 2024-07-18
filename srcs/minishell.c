/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:58:12 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/07 13:58:16 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_tools *tools)
{
	if (ft_strncmp(tools->split_rl[0], "exit", 4) == 0)
		return (exit_cmd(tools), 1);
	if (ft_strncmp(tools->split_rl[0], "cd", 2) == 0)
		return (cd_cmd(tools), 1);
	if (ft_strncmp(tools->split_rl[0], "env", 3) == 0)
		return (env_cmd(tools), 1);
	if (ft_strncmp(tools->split_rl[0], "echo", 4) == 0)
		return (echo_cmd(tools), 1);
	if (ft_strncmp(tools->split_rl[0], "pwd", 3) == 0)
		return (pwd_cmd(tools), 1);
	if (ft_strncmp(tools->split_rl[0], "unset", 5) == 0)
		return (unset_cmd(tools), 1);
	if (ft_strncmp(tools->split_rl[0], "export", 6) == 0)
		return (export_cmd(tools), 1);
	return (0);
}

void 	process_readline(t_tools *tools)
{
	if (tools->split_rl[0] == NULL)
		return ;
	if (pipes_in_prompt(tools) == 0)
	{
		if (is_builtin(tools) != 0)
			return ; 
		else
			execution(tools);
	}
}

void	run(char **envp)
{
	t_tools	tools;

	tools = (t_tools){0};
	tools.envp = envp;
	create_env_list(&tools);
	create_history(&tools);
	create_paths(&tools);
	while (1)
	{
		tools.rl = readline("SHITTYSHELL $> ");
		add_to_history(&tools);
		if (ft_strlen(tools.rl) != 0)
		{
			tools.split_rl = ft_split(tools.rl, ' ');
			if (!tools.split_rl)
				perror("malloc");
			free(tools.rl);
			tools.rl = NULL;
			process_readline(&tools);
			free_array(tools.split_rl);
			tools.split_rl = NULL;
		}
	}
}
