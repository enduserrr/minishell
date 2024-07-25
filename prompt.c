/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:56:36 by asalo             #+#    #+#             */
/*   Updated: 2024/07/25 18:15:48 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static size_t	ft_next_escape(char *prompt, size_t prev)
{
	while (prompt[prev])
	{
		if (prompt[prev] == '\\')
			return (prev);
		prev++;
	}
	return (prev);
}

static char	*working_dir(char esc)
{
	char	*pwd;
	char	*home;
	char	*val;
	int     cwd_flag;

	cwd_flag = 0;
	pwd = getenv("PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		cwd_flag = 1;
	}
	if (!pwd)
		return (NULL);
	val = ft_strdup(pwd);
	home = getenv("HOME");
	if (pwd && home && ft_strnstr(pwd, home, ft_strlen(pwd)) == pwd)
		ft_strinsrt(&val, "~", 0, ft_strlen(home));
	if (esc == 'W')
		ft_strinsrt(&val, "", 0, ft_strrchr_index(val, '/')
			+ !!ft_strcmp(pwd, "/"));
	if (cwd_flag == 1)
		free(pwd);
	return (val);
}

static char	*complex_val(char esc)
{
	char	*user;
	char	*hostname;

	if (esc == 'u')
	{
		user = getenv("USER");
		if (user)
			return (ft_strdup(user));
	}
	else if (ft_strchr("hH", esc))
	{
		hostname = getenv("HOSTNAME");
		if (hostname && esc == 'h')
			return (ft_substr(hostname, 0, ft_strchr_index(hostname, '.')));
		if (hostname && esc == 'H')
			return (ft_strdup(hostname));
	}
	return (NULL);
}

static char	*escape_val(char esc)
{
	if (esc == '[')
		return (ft_strdup("\001"));
	if (esc == ']')
		return (ft_strdup("\002"));
	if (esc == 'a')
		return (ft_strdup("\a"));
	if (esc == 'e')
		return (ft_strdup("\e"));
	if (esc == 'n')
		return (ft_strdup("\n"));
	if (esc == 'r')
		return (ft_strdup("\r"));
	if (esc == '\\')
		return (ft_strdup("\\"));
	if (esc == 's')
		return (ft_strdup("minishell"));
	if (ft_strchr("wW", esc))
		return (working_dir(esc));
	return (complex_val(esc));
}

char	*ft_expand_prompt(char *prompt)
{
	size_t	backslash;
	char	*val;

	if (!prompt)
		prompt = ft_strdup("\\h:\\W \\u\\$ ");
	else
		prompt = ft_strdup(prompt);
	if (prompt)
		backslash = ft_next_escape(prompt, 0);
	while (prompt && prompt[backslash])
	{
		val = escape_val(prompt[backslash + 1]);
        if (val == NULL)
            val = ft_strdup("");
		ft_strinsrt(&prompt, val, backslash, 1 + ft_strlen(val));
		backslash += ft_strlen(val);
		free(val);
		if (prompt)
			backslash = ft_next_escape(prompt, backslash);
	}
	return (prompt);
}

static char	*ft_get_prompt(void)
{
    char *prompt;

    prompt = ft_expand_prompt(getenv("PS1"));
    if (!prompt)
        prompt = ft_strdup("");
    return (prompt);
}