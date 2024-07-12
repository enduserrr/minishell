/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:00:26 by asalo             #+#    #+#             */
/*   Updated: 2024/07/12 16:02:17 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/tokens.h"

t_token	*new_token(char *content)
{
	t_token	*new;

	if (!content)
		return (ft_perror(MEM_ERR, "creating token content"), NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (ft_perror(MEM_ERR, "creating token"), free(content), NULL);
	new->id = WORD;
	new->content = content;
	new->next = NULL;
	return (new);
}

void	tokens_free(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = next;
	}
}

size_t  unquoted_char(char *s, const char *chars, const char *quotes)
{
    size_t  i;
    char    quote;

    i = 0;
    quote = 0;
    while (s[i])
    {
        if (!quote && ft_strchr(chars, s[i]))
            break ;
        if (!quote && ft_strchr(quotes, s[i]))
            break ;
        else if (s[i] == quote)
            quote = 0;
        i++; 
    }
    return (i);
}

t_token *put_tkn(t_token *tokens, const char *title)
{
    if (title)
        printf("\e[1;33m%s\e[0m\n", title);
    if (!tokens)
        printf("No tokens\n");
    while (tokens)
    {
        if (tokens->id == WORD)
            printf("[WORD] ");
        else if (tokens->id == IN_FILE)
            printf("[IN_FILE] ");
        else if (tokens->id == OUT_FILE)
            printf("[OUT_FILE] ");
		else if (tokens->id == HEREDOC_EOF)
			printf("[HEREDOC_EOF] ");
		else if (tokens->id == OUT_A_FILE)
			printf("[OUT_A_FILE] ");
		else if (tokens->id == COMMAND)
			printf("[COMMAND] ");
		else if (tokens->id == OPERATOR)
			printf("[OPERATOR] ");
		else if (tokens->id == IN_REDIR)
			printf("[IN_RED] ");
		else if (tokens->id == OUT_REDIR)
			printf("[OUT_RED] ");
		else if (tokens->id == HEREDOC)
			printf("[HEREDOC] ");
		else if (tokens->id == OUT_A_REDIR)
			printf("[OUT_A_RED] ");
		else if (tokens->id == PIPE)
			printf("[PIPE] ");
		printf("[%s]\n", tokens->content);
		tokens = tokens->next;
	}
	return (tokens);
}