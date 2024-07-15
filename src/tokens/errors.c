/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:52:11 by asalo             #+#    #+#             */
/*   Updated: 2024/07/14 15:24:27 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/tokens.h"

static void put_stderr(char *s, char *context)
{
    int	i;
    int j;

	i = 0;
    j = 0;
	while (s[i])
		i++;
    if (context[j])
        while (context[j])
            j++;
	write(2, "Error: ", 7);
	write(2, s, i);
    write(2, " ", 1);
    write(2, context, j);
	write(2, "\n", 1);
}

static int	set_stderr(int err, char *context)
{
	if (err == ERRNO_ERR)
		return (perror(context), errno);
	if (err == MEM_ERR)
		return (put_stderr("memory allocation failed while %s", context), err);
	if (err == TKN_SYNTAX_ERR)
		return (put_stderr("syntax error near unexpected token `%s'", context)
			, err);
	if (err == REDIR_ERR)
		return (put_stderr("%s: ambiguous redirect", context), 1);
	if (err == IS_DIR_ERR)
		return (put_stderr("%s: is a directory", context), err);
	if (err == UNKNOWN_CMD_ERR)
		return (put_stderr("%s: command not found", context), err);
	if (err == NO_FILE_ERR)
		return (put_stderr("%s: No such file or directory", context), 127);
	if (err == UNSET_ERR)
		return (put_stderr("%s not set", context), 1);
	return (0);
}

int	handle_perror(int err, char *context)
{
	int	i;

	write(2, "minishell: ", 11);
	i = set_stderr(err, context);
	if (err != ERRNO_ERR)
		write(2, "\n", 1);
	return (i);
}