/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:06 by asalo             #+#    #+#             */
/*   Updated: 2024/08/02 09:37:25 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void 	process_cmds(t_data *data)
{
	if (data->cmds == NULL)
        return ;
    if (is_builtin(data) != 0)
			return ;
	else
        execution(data);
}

void run(t_data *data)
{
    char    *input;
    int     status;
    t_token *tokens;

    status = 0;
    while(1)
    {
        signal(SIGINT, signal_handler);
        input = readline("$> ");
        if (!input)
        {
            write(1, "exit\n",  5);
            break ;
        }
        if (input[0])
        {
            add_history(input);
            tokens = ft_token(&status, input);
            data->cmds = ft_parse(&status, tokens);
            process_cmds(data);
            free_commands(data->cmds);
        }
        else
            continue ;
    }
    free_all(data);
}

int main(int ac, char **av, char **envp)
{
    (void)av;
	t_data  data;

    if (ac != 1)
        return (bold_red(1, "No args accepted\n"), 0);
    signal(SIGQUIT, SIG_IGN);
    data = (t_data){0};
    data.envp = envp;
    create_env_list(&data);
    create_paths(&data);
    bold_green(1, WLCM);
	run(&data);
	return (0);
}
