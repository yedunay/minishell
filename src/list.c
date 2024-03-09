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

// Adds the node 'to_add' at the end of the list.
void	lst_add(t_list **lst, t_list *to_add)
{
	t_list	*node;

	node = lst_last(*lst);
	if (node)
		lst_link(node, to_add);
	else
		*lst = to_add;
}

// Returns the last node of the list.
t_list	*lst_last(t_list *lst)
{
	while (lst && lst->nxt)
		lst = lst->nxt;
	return (lst);
}

// Links the list nodes 'n1' and 'n2', so that 'n2' follows 'n1'.
void	lst_link(t_list *n1, t_list *n2)
{
	if (n1)
		n1->nxt = n2;
	if (n2)
		n2->pre = n1;
}

// Allocates (with malloc(3)) and returns a new node.
// The member variable 'val' is initialized with the value of the parameter
// 'value'. 'nxt' and 'pre' are initialized to NULL.
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

// Deletes and frees the given node and every successor of that node, using the
// function 'del' and free(3). 
// Finally, the pointer to the list must be set to NULL.
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
