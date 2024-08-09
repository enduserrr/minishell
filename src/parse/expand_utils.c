/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:33:34 by asalo             #+#    #+#             */
/*   Updated: 2024/08/09 12:34:10 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

/**
 * @brief	Scans a str to find the next env var ref. Handles quoted sections
 *			and backslashes. Returns position of the next env ref.
 */
static ssize_t	next_env(char *str, size_t env, char is_hd, char backslash)
{
	static char	quote;

	while (str[env])
	{
		if (str[env] == '$' && !backslash && (is_hd || quote != '\''))
		{
			if (str[env + 1] == '?')
				return (env);
			if (ft_isalnum(str[env + 1]) || ft_strchr("!#$&*-?@_", str[env + 1])
				|| (str[env + 1] == '\\' && str[env + 2] != '\\')
				|| (!is_hd && !quote && ft_strchr("\'\"", str[env + 1])))
				return (env);
		}
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

static size_t	env_len(char *s)
{
	size_t	len;
	size_t	len2;

	if (s[1] == '?')
		return (2);
	if (ft_strchr("\'\"", s[1]))
		return (1);
	if (ft_isdigit(s[1]) || ft_strchr("!#$&*-?@\\", s[1]))
		return (2);
	len2 = 0;
	if (s[0] == '$')
	{
		len2++;
		while (ft_isalnum(s[len2]) || s[len2] == '_')
			len2++;
		return (len2);
	}
	len = 2;
	while (ft_isalnum(s[len]) || s[len] == '_')
		len++;
	return (len);
}

static char	*check_env(char *var, size_t len, t_exit *state, t_env *env_list)
{
	char	temp;
	char	*env;

	if (var[0] == '?')
		return (ft_itoa(state->state));
	if (ft_isdigit(var[0]) || ft_strchr("!#$&*-@_\\\'\"", var[0]))
		return (NULL);
	temp = var[len];
	var[len] = '\0';
	env = find_env(var, env_list);
	var[len] = temp;
	if (env)
		return (env);
	return (NULL);
}

static void	backlash_escpe(char **s, char is_hd)
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
		if ((*s)[i] == '\\' && (is_hd || !quote))
			ft_strinsrt(s, "", i, 1);
	}
}

char	expand_env(char **s, t_exit *state, char id, t_env *env_list)
{
	size_t	env;
	size_t	len;
	char	*val;

	env = next_env(*s, 0, id == HEREDOC, 0);
	while (env < ft_strlen(*s) && (*s)[env])
	{
		len = env_len(*s + env);
		val = check_env(*s + env + 1, len - 1, state, env_list);
		if (!val && env == 0 && len == ft_strlen(*s))
		{
			if (id == IN_FILE || id == OUT_FILE || id == OUT_A_FILE)
				return (set_err(1, "ambiguous redirect", state));
			return (REMOVE);
		}
		if (ft_strinsrt(s, val, env, len) != NULL)
			return (1);
		if (val != NULL)
			env += ft_strlen(val);
		else
			env += len;
		free(val);
		env = next_env(*s, env, id == HEREDOC, 0);
	}
	return (backlash_escpe(s, id == HEREDOC), 0);
}
