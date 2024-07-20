/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/20 12:43:47 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/tokens.h"

int main(int ac, char **av)
{
    if (ac < 2)
        return (1);
    int i = 0;
    while (av[1][i])
        i++;
    // char *input = malloc(sizeof(char) * (i + 1));
    char    *input = ft_calloc(i + 1, sizeof(char));
    ft_strcpy(input, av[1]);
    int status = 0;
    t_token *tokens = tokenizer(&status, input);
    if (!tokens)
        return (1);
    t_cmd *cmds = parse(&status, tokens);
    if (!cmds)
        return (1);
    free_cmds(cmds);
    return (0);
}