/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/17 19:11:58 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/tokens.h"

int	main(int ac, char **av)
{
    t_token *tokens;
    t_cmd   *commands;

    if (ac == 2)
    {
        tokens = tokenizer(0, av[1]);
        commands = parse(0, tokens);
        put_cmd(commands);
        free_cmds(commands);
        free_tokens(tokens);
    }
    write(1, "\n", 1);
    return (0);
}