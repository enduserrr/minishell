/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:20:32 by asalo             #+#    #+#             */
/*   Updated: 2024/07/21 12:54:21 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

/**
 * @brief	Scans a str to find the next env var ref.
 *			Handles quoted sections and backslashes.
 *			Returns position of the next env ref.
 */
static size_t	next_env(char *str, size_t env, char is_heredoc)
{
	static char	quote;
	char		backslash;

	backslash = 0;
	while (str[env + 1])
	{
		if (str[env] == '$' && !backslash && (is_heredoc || quote != '\'')
			&& (ft_isalnum(str[env + 1]) || ft_strchr("!#$&*-?@_", str[env + 1])
				|| (str[env + 1] == '\\' && str[env + 2] != '\\')
				|| (!is_heredoc && !quote && ft_strchr("\'\"", str[env + 1]))))
			return (env);
		if (!quote && ft_strchr("\'\"", str[env]))
			quote = str[env];
		else if (str[env] == quote)
			quote = 0;
		if (!backslash && str[env] == '\\')
			backslash = 1;
		else
			backslash = 0;
		env++;
	}
	quote = 0;
	return (env + 1);
}

/**
 * @brief	Counts the len of an env var starting with '$'.
 *			Accounts for special chars following the '$'.
 */
static size_t	env_len(char *s)
{
	size_t	len;

	if (ft_strchr("\'\"", s[1]))
		return (1);
	if (ft_isdigit(s[1]) || ft_strchr("!#$&*-?@\\", s[1]))
		return (2);
	len = 2;
	while (ft_isalnum(s[len]) || s[len] == '_')
		len++;
	return (len);
}

/**
 * @brief	Checks if a given env var exists and gets its value.
 */
static char	*check_env(char *var, size_t len, int status)
{
	char	temp;
	char	*env;

	if (ft_isdigit(var[0]) || ft_strchr("!#$&*-@_\\\'\"", var[0]))
		return (NULL);
	if (var[0] == '?')
		return (ft_itoa(status));
	temp = var[len];
	var[len] = '\0';
	env = getenv(var);
	var[len] = temp;
	if (env)
		return (ft_strdup(env));
	return (NULL);
}

/**
 * @brief	Checks a string to handle escape characters.
 *			Removes them if needed
 *			(whether in HEREDOC context or quoted)
 */
static void	backlash_escpe(char **s, char is_heredoc)
{
	size_t	i;
	char	quote;

	quote = 0;
	i = -1;
	while ((*s)[++i + 1])
	{
		if (!quote && ft_strchr("\'\"", (*s)[i]))
			quote = (*s)[i];
		else if ((*s)[i] == quote)
			quote = 0;
		if ((*s)[i] == '\\' && (is_heredoc || !quote))
			ft_strinsrt(s, "", i, 1);
	}
}

/**
 * @brief	Expands env vars in the given str.
 *			(find & replace env vars with the corresponding values)
 *			Calls funcs for redirs, escape chars etc.
 */
char	ft_expand(char **s, int status, char id)
{
	size_t	env;
	size_t	len;
	char	*val;

	env = next_env(*s, 0, id == HEREDOC);
	while ((*s)[env])
	{
		len = env_len(*s + env);
		val = check_env(*s + env + 1, len - 1, status);
		if (!val && env == 0 && len == ft_strlen(*s))
		{
			if (id == IN_FILE || id == OUT_FILE || id == OUT_A_FILE)
				return (set_err(AMBIG_REDIR_ERR, *s), RETURN_FAILURE);
			return (RMV);
		}
		if (ft_strinsrt(s, val, env, len))
			env += ft_strplen(val);
		free(val);
		env = next_env(*s, env, id == HEREDOC);
	}
	return (backlash_escpe(s, id == HEREDOC), RETURN_SUCCESS);
}
