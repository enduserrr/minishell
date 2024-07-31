/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/31 18:58:04 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include <stdbool.h>

//eemelin main
volatile sig_atomic_t g_signal_status = 0;

// static int	only_space(char *line)
// {
// 	size_t	i;

// 	if (!line)
// 		return (1);
// 	i = -1;
// 	while (line[++i])
// 		if (!ft_isspace(line[i]))
// 			return (0);
// 	return (1);
// }

bool	white_space(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

void rl_handler(int sig)
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    (void)sig;
}

void sig_handler(int sig)
{
    g_signal_status = 1;
    (void)sig;
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

int	ftt_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/*sigaction for more control*/
void run(t_data *data, int *status)
{
    char    *input;
    t_token *tokens;

    while(1)
    {
        g_signal_status = 0;  /*Handle SIGINT (Ctrl-C)*/
        input = readline("prompt$ ");
        signal(SIGINT, sig_handler); /*Restore default handler*/
        if (!*input)/*!isatty(STDIN_FILENO)*/
        {
            printf("what\n");
            continue ;
        }
        if (!input)
        {
            write(1, "exit\n", 5);
            break ;
        }
        else
        {
            add_history(input);
            tokens = ft_token(status, input);
            data->cmds = ft_parse(status, tokens);
            process_cmds(data);
            free_commands(data->cmds);
            *status = data->exit_code;
        }
    }
    free_all(data);
}

static void	config_term(void)
{
	struct termios	new_term;

	if (tcgetattr(STDIN_FILENO, &new_term) == -1)
    {
        perror("tcgetattr");
        return ;
    }
    new_term.c_lflag &= ~(ICANON);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_term) == -1)
    {
        perror("tcgetattr");
        return ;
    }
}

int main(int ac, char **av, char **envp)
{
    (void)av;
	t_data  data;
    static int  status;

    if (ac != 1)
        return (bold_red(1, "No args accepted\n"), 0);
    signal(SIGQUIT, SIG_IGN);
    data = (t_data){0};
    data.envp = envp;
    create_env_list(&data);
    create_paths(&data);
    bold_green(1, WLCM);
    config_term();
	run(&data, &status);
    status = data.exit_code;
	return (status);
}
