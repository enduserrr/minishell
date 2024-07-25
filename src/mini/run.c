/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:03:38 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/23 16:03:40 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../incs/minishell.h"
/*
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
	//create_history(&tools);
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
}*/
