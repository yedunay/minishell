/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:40:22 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:23:46 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lst_add(t_list **lst, t_list *to_add)
{
	t_list	*node;

	node = lst_last(*lst);
	if (node)
		lst_link(node, to_add);
	else
		*lst = to_add;
}

t_list	*lst_last(t_list *lst)
{
	while (lst && lst->nxt)
		lst = lst->nxt;
	return (lst);
}

void	lst_link(t_list *n1, t_list *n2)
{
	if (n1)
		n1->nxt = n2;
	if (n2)
		n2->pre = n1;
}

t_list	*lst_new(void *value, size_t size)
{
	t_list	*lstnode;

	lstnode = (t_list *)p_malloc(sizeof (t_list));
	lstnode->val = p_malloc(size);
	ft_memcpy(lstnode->val, value, size);
	lstnode->nxt = NULL;
	lstnode->pre = NULL;
	return (lstnode);
}

void	lst_clear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*nxt_node;

	node = *lst;
	while (node)
	{
		nxt_node = node->nxt;
		lst_delone(node, del);
		node = nxt_node;
	}
	*lst = NULL;
}
