/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:51:36 by eleppala          #+#    #+#             */
/*   Updated: 2023/11/29 15:09:47 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "../libft.h"
# include <stdlib.h> 
# include <unistd.h> 

char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_mod(char *free_line, char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
void	null_string(char *s);

#endif
