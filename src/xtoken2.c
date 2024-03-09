/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xtoken2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:03:26 by ydunay            #+#    #+#             */
/*   Updated: 2024/02/24 13:49:38 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Clears the list of xtokens.
void	xtoklst_clear(t_list **xtoks)
{
	t_list	*node;
	t_list	*nxt_node;

	node = *xtoks;
	while (node)
	{
		nxt_node = node->nxt;
		lst_clear(node->val, free);
		node = nxt_node;
	}
	lst_clear(xtoks, free);
}

// Adds the 'to_add' xchar list nodes right before the 'pos' position at 'xtok'.
void	xtok_add_many(t_xtoken *xtok, t_list *pos, t_list *to_add)
{
	lst_add_many(&(xtok->val), pos, to_add);
}

// Adds 'c' at the end of 'xtok' with the given flags.
void	xtok_addc(t_xtoken *xtok, char c, int x_flag, int q_flag)
{
	t_xchar	xc;

	xc = xc_new(c, x_flag, q_flag);
	lst_add(&(xtok->val), lst_new(&xc, sizeof(xc)));
}

// Removes and frees the given 'to_rm' node from the xtoken's value.
void	xtok_rm_one(t_xtoken *xtok, t_list *to_rm)
{
	t_list	*lst;

	lst = xtok->val;
	lst_rm_one(&lst, to_rm, free);
}

// Removes and frees 'n' nodes from the xtoken's value, starting from 'to_rm'.
void	xtok_rm_many(t_xtoken *xtok, t_list *to_rm, size_t n)
{
	t_list	*lst;

	lst = xtok->val;
	lst_rm_many(&lst, to_rm, n, free);
}
