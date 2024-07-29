/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/29 10:03:50 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//eemelin main

void 	process_cmds(t_data *data)
{
	if (data->cmds == NULL)
        return ;
    if (data->cmds->av[0] == NULL)
    {
        execution(data);
        return ;
    }
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
        status = 0;
        input = readline("$> ");
        if (input[0])
        {
            add_history(input);
            tokens = ft_token(&status, input);
            data->cmds = ft_parse(&status, tokens);
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
	printf("\33[1;91m%s\e[0m", WLCM);
	run(&data);
	return (0);
}
