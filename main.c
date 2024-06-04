/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:40:42 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/31 13:37:54 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
 * Pelkka main funktio lisaa checkkeja tarvittaessa
 * checkkaa ettei argumentteja - ohjelman suoritus run()
 */
t_sig	g_sig;

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
	{
		printf("No args accepted");
		return (0);
	}
	run(envp);
	return (0);
}
