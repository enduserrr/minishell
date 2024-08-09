/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:19:27 by eleppala          #+#    #+#             */
/*   Updated: 2024/08/09 12:23:48 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "general.h"

char				*dup_rest(char *s, int start);
char				*ft_strdup_till_c(const char *s1, char c);
char				*ft_get_cwd(t_env *env);

#endif
