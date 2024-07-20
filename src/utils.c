/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:55:15 by asalo             #+#    #+#             */
/*   Updated: 2024/07/20 14:15:03 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/tokens.h"

/**
 * @brief   ssize_t range from -1 to SIZE_MAX
 *          Like size_t plus range for return failure.
*/
size_t	ft_strplen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
ssize_t set_char(char *s, char c, ssize_t i)
{
    if (c == '/' && i < 0)
		return (ft_strlen(s));
	if (!s || i < 0 || i > (ssize_t)ft_strlen(s))
		return (-1);
	s[i] = c;
	return (i);
}

static void write_err(char *s, char *context)
{
    int	i;
    int j;

	i = 0;
    j = 0;
	while (s[i])
		i++;
	write(2, "Error: ", 7);
	write(2, s, i);
	if (context[j])
	{
        while (context[j])
            j++;
		write(2, context, j);
	}
	write(2, "\n", 1);
}

static int	error_case(int err, char *context)
{
	if (err == ERRNO_ERR)
		return (perror(context), errno);
	if (err == MEM_ERR)
		return (write_err("memory allocation failed while ", context), err);
	if (err == TKN_SYNTAX_ERR)
		return (write_err("syntax error near unexpected token: ", context)
			, err);
	if (err == AMBIG_REDIR_ERR)
		return (write_err("%s: ambiguous redirect", context), 1);
	if (err == IS_DIR_ERR)
		return (write_err("%s: is a directory", context), err);
	if (err == UNKNOWN_CMD_ERR)
		return (write_err("%s: command not found", context), err);
	if (err == NO_FILE_ERR)
		return (write_err("%s: No such file or directory", context), 127);
	if (err == UNSET_ERR)
		return (write_err("%s not set", context), 1);
	return (0);
}

int	parsing_err(int err, char *context)
{
	int	i;

	write(2, "minishell: ", 11);
	i = error_case(err, context);
	if (err != ERRNO_ERR)
		write(2, "\n", 1);
	return (i);
}
