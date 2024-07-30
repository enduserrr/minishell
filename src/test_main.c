/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/30 16:14:49 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//eemelin main
volatile sig_atomic_t g_signal_status = 0;

/**
 * @brief   Handle SIGNINT (Ctrl-C).
 *          Clear the line and move to new, redisplay the prompt.
*/
void handle_sigint(int sig)
{
    (void)sig;
    g_signal_status = SIGINT;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

/**
 * @brief   Ignore SIGQUIT (Ctrl-\)
*/
/*void handle_sigquit(int sig)
{
     (void)sig;
}*/

/**
 * @brief   Handle SIGTERM (Ctrl+D).
 *          Clear the line and move to new, redisplay the prompt.
*/
void    handle_sigterm(int sig)
{
    (void)sig;
    g_signal_status = SIGTERM;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

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
            bold_white(1, "command not found\n");
    }
    free_all(data);
}

int main(int ac, char **av, char **envp)
{
    (void)av;
	t_data  data;
    static int  flag;

    flag = 0;
    if (ac != 1)
        return (bold_red(1, "No args accepted\n"), 0);
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);/*If not allowed make separate func*/
    signal(SIGTERM, handle_sigterm);
    data = (t_data){0};
    data.envp = envp;
    create_env_list(&data);
    create_paths(&data);
    bold_green(1, WLCM);
	run(&data);
	return (0);
}
