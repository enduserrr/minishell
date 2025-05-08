#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "general.h"

char				*dup_rest(char *s, int start);
char				*ft_strdup_till_c(const char *s1, char c);
char				*ft_get_cwd(t_env *env);

#endif
