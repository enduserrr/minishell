/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:06 by asalo             #+#    #+#             */
/*   Updated: 2024/08/02 12:31:42 by asalo            ###   ########.fr       */
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

void run(t_data *data, t_exit *state)
{
    char    *input;
    t_token *tokens;

    while(1)
    {
        signal(SIGINT, signal_handler);
        input = readline("$> ");
        if (!input)
        {
            state->state = 1;
            write_fd(1, WHITE, "exit\n");
            printf("%d\n", state->state);
            break ;
        }
        if (input[0])
        {
            add_history(input);
            tokens = ft_token(state, input);
            data->cmds = ft_parse(state, tokens);
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
    static  t_exit  exit_state;

    if (ac != 1)
        return (write_fd(1, RED, "No args accepted\n"), 0);
    signal(SIGQUIT, SIG_IGN);
    exit_state = (t_exit){0};
    data = (t_data){0};
    data.envp = envp;
    data.exit_code = &exit_state;
    create_env_list(&data);
    create_paths(&data);
    write_fd(1, GREEN, WLCM);
	run(&data, &exit_state);
	return (0);
}
