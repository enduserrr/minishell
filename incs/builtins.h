/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:19:27 by eleppala          #+#    #+#             */
/*   Updated: 2024/07/23 13:19:31 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct 		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;

}					t_env;

char 	*dup_rest(char *s, int start);
char	*ft_strdup_till_c(const char *s1, char c);

#endif