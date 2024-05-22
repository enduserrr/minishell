/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:40:42 by eleppala          #+#    #+#             */
/*   Updated: 2024/05/20 10:40:45 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
 * Pelkka main funktio lisaa checkkeja tarvittaessa
 * checkkaa ettei argumentteja - ohjelman suoritus run()
 */

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
