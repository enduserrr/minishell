/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/25 10:23:53 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

//eemelin main

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