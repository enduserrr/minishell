/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:55:15 by asalo             #+#    #+#             */
/*   Updated: 2024/07/30 11:15:37 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

/**
 * @brief	Write error to stderr with or without context.
 */
#define RESET       "\033[0m"
#define BOLD_RED    "\033[1;91m"
#define BOLD_GREEN  "\033[1;92m"
#define BOLD_YELLOW "\033[1;93m"


static void write_fd(int fd, const char *color, const char *text)
{
    write(fd, color, ft_strlen(color));
    write(fd, text, ft_strlen(text));
    write(fd, RESET, ft_strlen(RESET));
}

/**
 * @brief	Write error to stderr with or without context.
 */
static void write_err(char *s, char *context)
{
    int	i;
    int j;

	i = 0;
    j = 0;
	while (s[i])
		i++;
	write_fd(2, BOLD_RED, "\nError: ");
	write(2, s, i);
	if (context[j])
	{
        while (context[j])
            j++;
		write(2, " ('", 3);
		write(2, context, j);
		write(2, "')", 2);
	}
}

/**
 * @brief	Custom error cases.
 *			Returns an exit code.
 */
static int	error_case(int err, char *context)
{
	if (err == ERRNO_ERR)
		return (perror(context), errno);
	if (err == MEM_ERR)
		return (write_err("memory allocation fail while", context), err);
	if (err == TKN_SYNTAX_ERR)
		return (write_err("syntax error near", context)
			, err);
	if (err == AMBIG_REDIR_ERR)
		return (write_err("ambiguous redirect", context), 1);
	if (err == IS_DIR_ERR)
		return (write_err("is a directory", context), err);
	if (err == UNKNOWN_CMD_ERR)
		return (write_err("command not found", context), err);
	if (err == NO_FILE_ERR)
		return (write_err("no such file or directory", context), 127);
	if (err == UNSET_ERR)
		return (write_err("not set", context), 1);
	return (0);
}

/**
 * @brief	Frame through which the error output funcs are called.
 *			Returns an exit code to be used with exit().
 */
int	set_err(int err, char *context)
{
	int	i;

	write(2, "minishell: ", 11);
	i = error_case(err, context);
	if (err != ERRNO_ERR)
		write(2, "\n", 1);
	return (i);
}
