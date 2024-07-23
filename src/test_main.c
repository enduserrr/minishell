/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/23 11:29:26 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parse.h"

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
}