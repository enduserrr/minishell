/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:18:54 by asalo             #+#    #+#             */
/*   Updated: 2024/06/04 08:25:26 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		cpy_variable(char *new_arg, const char *env_value, int pos)
{
	int		i;

	i = 0;
	while (env_value[i])
		new_arg[pos++] = env_value[i++];
	return (i);
}

char			*expand(char *arg, t_env *env, int ret)
{
	t_exps	ex;
}
