/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:31:51 by asalo             #+#    #+#             */
/*   Updated: 2024/06/04 08:17:34 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void clear_garbage(t_list **list_ptr, char *type, void (*del)(void*))
{
	if (!list_ptr || !del)
		return ;
	if (type == "list")
		ft_lstclear(list_ptr, del);
	else if (type == "node")
		ft_lstdelone(*list_ptr, del);
}

void clear_all_lists(t_list *lst, void (*del)(void *))
{
	ft_lstcear(&(lst->tkn), del);
	ft_lstclear(&(lst->env), del);
	ft_lstclear(&(lst->tools), del);
	ft_lstclear(&(lst->sig), del);
	ft_lstclear(&(lst->exps), del);
}

void add_node(t_list **list, void *content)
{
	t_list *new_node = create_node(content);
	if (!new_node)
		return;
	new_node->next = *list;
	*list = new_node;
}

void init_lists(t_list *lst)
{
	lst->tkn = NULL;
	lst->env = NULL;
	lst->tools = NULL;
	lst->sig = NULL;
	lst->exps = NULL;
}
t_list *create_node(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return NULL;
	new_node->content = content;
	new_node->next = NULL;
	return new_node;
}
