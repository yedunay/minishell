/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:48:08 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:23:38 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lst_delone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->val);
	free(lst);
}

void	lst_rm_one(t_list **lst, t_list *to_rm, void (*del)(void *))
{
	if (*lst == to_rm)
		*lst = (*lst)->nxt;
	lst_link(to_rm->pre, to_rm->nxt);
	lst_delone(to_rm, del);
}

void	lst_rm_many(t_list **lst, t_list *to_rm, size_t n, void (*del)(void *))
{
	t_list	*prev;
	t_list	*next;

	if (!*lst && !to_rm)
		return ;
	if (*lst == to_rm)
		*lst = lst_move(*lst, n);
	prev = to_rm->pre;
	next = to_rm;
	while (n-- > 0 && next)
	{
		to_rm = next;
		next = next->nxt;
		lst_delone(to_rm, del);
	}
	lst_link(prev, next);
}

t_list	*lst_move(t_list *node, int n)
{
	while (n != 0)
	{
		if (!node)
			return (NULL);
		if (n > 0)
		{
			node = node->nxt;
			--n;
		}
		else
		{
			node = node->pre;
			++n;
		}
	}
	return (node);
}

size_t	lst_size(t_list *lst)
{
	size_t	size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst->nxt;
		size++;
	}
	return (size);
}
