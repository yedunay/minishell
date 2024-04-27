/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:53:28 by ydunay            #+#    #+#             */
/*   Updated: 2024/02/17 18:43:37 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*lst_first(t_list *lst)
{
	while (lst && lst->pre)
		lst = lst->pre;
	return (lst);
}

void	lst_split(t_list *node)
{
	t_list	*prev;

	if (!node)
		return ;
	prev = node->pre;
	if (prev)
		prev->nxt = NULL;
	node->pre = NULL;
}
