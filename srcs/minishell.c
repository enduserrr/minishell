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

/*
 * readline loppiin niin kauan etta komento on "exit"
 * tassa kohtaa iha vaa checkina jos komento on joku builtin.
 */

void	kaikki_mita_parsetukseen_tulee(void)
{
	// Tassa kohtaa joku varmaan parsettaa jotakin, ehka muutaman filen verran.
}

void	if_builtin(t_tools *tools)
{
	if (ft_strncmp(tools->split_rl[0], "exit", 4) == 0)
		exit_cmd(tools);
	if (ft_strncmp(tools->split_rl[0], "cd", 2) == 0)
		cd_cmd(tools);
	if (ft_strncmp(tools->split_rl[0], "env", 3) == 0)
		env_cmd(tools);
	if (ft_strncmp(tools->split_rl[0], "echo", 4) == 0)
		echo_cmd(tools);
	if (ft_strncmp(tools->split_rl[0], "pwd", 3) == 0)
		pwd_cmd(tools);
	if (ft_strncmp(tools->split_rl[0], "unset", 5) == 0)
		unset_cmd(tools);
	if (ft_strncmp(tools->split_rl[0], "export", 6) == 0)
		export_cmd(tools);
}

void	run(char **envp)
{
	t_tools	tools;

	tools = (t_tools){0};
	tools.envp = envp;
	while (1)
	{
		tools.rl = readline("$>");
		kaikki_mita_parsetukseen_tulee();
		tools.split_rl = ft_split(tools.rl, ' ');
		free(tools.rl);
		if_builtin(&tools);
		free_array(tools.split_rl);
		tools.split_rl = NULL;
	}
}
