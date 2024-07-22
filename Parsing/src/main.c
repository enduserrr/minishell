/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:04:43 by asalo             #+#    #+#             */
/*   Updated: 2024/07/21 14:10:42 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/general.h"

volatile sig_atomic_t g_sig = 0;

void signal_handler(int signal)
{
    g_sig = 1;
    (void)signal;
}


int main(int ac, char **av)
{
    if (ac != 1)
        exit (0);
    signal(SIGINT, SIG_IGN);
}