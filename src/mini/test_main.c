/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/25 12:06:54 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

//eemelin main
int	is_builtin(t_data *data)
{
	if (ft_strncmp(data->cmds->av[0], "exit", 4) == 0)
		return (exit_cmd(data), 1);
    if (ft_strncmp(data->cmds->av[0], "cd", 2) == 0)
		return (cd_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "env", 3) == 0)
		return (env_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "echo", 4) == 0)
		return (echo_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "pwd", 3) == 0)
		return (pwd_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "unset", 5) == 0)
		return (unset_cmd(data), 1);
	if (ft_strncmp(data->cmds->av[0], "export", 6) == 0)
		return (export_cmd(data), 1);
	return (0);
}

void 	process_cmds(t_data *data)
{
	if (data->cmds->av[0] == NULL)
		  return ;
    if (is_builtin(data) != 0)
			return ; 
	else
        execution(data);
}

static void run(t_data *data)
{
    char    *input;
    int     status;
    t_token *tokens;

    while(1)
    {
        input = readline("$> ");
        if (input[0])
        {
            tokens = ft_tokens(&status, input);
            data->cmds = ft_parse(&status, tokens);
            printf("\n--------end of parsing-------------\n\n");
            process_cmds(data);
            free_commands(data->cmds);
        }
    }
    free_all(data);
}

int main(int ac, char **av, char **envp)
{
    (void)av;
	t_data  data;

    data = (t_data){0};
    data.envp = envp;
    create_env_list(&data);
    create_paths(&data);
    if (ac != 1)
	{
		printf("No args accepted");
		return (0);
	}

	printf("%s", WELCOME);
	run(&data);
	return (0);
}


// artun main
/*
int main(int ac, char **av)
{
    char    *input;
    int     status;
    t_token *tokens;
    t_cmd   *commands;

    if (ac < 2)
        return (1);
    int i = 0;
    while (av[1][i])
        i++;
    input = ft_calloc(i + 1, sizeof(char));
    ft_strcpy(input, av[1]);
    status = 0;
    tokens = ft_tokens(&status, input);
    if (!tokens)
        return (1);
    commands = ft_parse(&status, tokens);
    if (!commands)
        return (1);
    free_commands(commands);
    return (0);
}*/