/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:56:36 by asalo             #+#    #+#             */
/*   Updated: 2024/07/25 18:40:08 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static size_t ft_next_escape(const char *prompt, size_t prev)
{
    while (prompt[prev]) {
        if (prompt[prev] == '\\') {
            return prev;
        }
        prev++;
    }
    return prev;
}

static char *working_dir(char esc)
{
    char	*pwd = getenv("PWD");
    char	*home = getenv("HOME");
    char	*val;
    int		cwd_flag = 0;

    if (!pwd)
	{
        pwd = getcwd(NULL, 0);
        cwd_flag = 1;
    }
    if (!pwd)
        return (NULL);
    val = ft_strdup(pwd);
    if (home && ft_strnstr(pwd, home, ft_strlen(home)) == pwd)
        ft_strinsrt(&val, "~", 0, ft_strlen(home));
    if (esc == 'W')
        ft_strinsrt(&val, "", 0, ft_strrchr_index(val, '/') + !!ft_strcmp(pwd, "/"));
    if (cwd_flag)
        free(pwd);
    return (val);
}

static char *complex_val(char esc) 
{
	char	*user;
	char	*hostname;

    if (esc == 'u')
	{
        user = getenv("USER");
        if (user)
            return (ft_strdup(user));
    }
	else if (esc == 'h' || esc == 'H')
	{
        hostname = getenv("HOSTNAME");
        if (hostname)
		{
            if (esc == 'h')
                return (ft_substr(hostname, 0, ft_strchr_index(hostname, '.'))); 
			else
                return (ft_strdup(hostname));
        }
    }
    return (NULL);
}

static char	*escape_val(char esc) 
{
    if (esc == '[')
		return ft_strdup("\001");
    if (esc == ']')
		return ft_strdup("\002");
    if (esc == 'a')
		return ft_strdup("\a");
    if (esc == 'e')
		return ft_strdup("\e");
    if (esc == 'n')
		return ft_strdup("\n");
    if (esc == 'r')
		return ft_strdup("\r");
    if (esc == '\\')
		return ft_strdup("\\");
    if (esc == 's')
		return ft_strdup("minishell");
    if (esc == 'w' || esc == 'W')
		return (working_dir(esc));
    return complex_val(esc);
}

char	*ft_expand_prompt(const char *prompt)
{
    size_t	backslash;
    char	*expanded_prompt;
    char	*val;

	backslash = 0;
	expanded_prompt = ft_strdup(prompt ? prompt : "\\h:\\W \\u\\$ ");
    while (expanded_prompt && (backslash = ft_next_escape(expanded_prompt, backslash)) < ft_strlen(expanded_prompt))
	{
        val = escape_val(expanded_prompt[backslash + 1]);
        if (!val)
            val = ft_strdup("");
        ft_strinsrt(&expanded_prompt, val, backslash, 1 + ft_strlen(val));
        backslash += ft_strlen(val);
        free(val);
    }
    return expanded_prompt;
}

char	*ft_get_prompt(void)
{
    char *prompt;
	
	prompt = ft_expand_prompt(getenv("PS1"));
    if (!prompt)
        prompt = ft_strdup("");
    return prompt;
}
