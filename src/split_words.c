/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:52:45 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:17:11 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_delim(t_xchar xc)
{
	if (is_blankchr(xc.c) && xc.x == EXPANDED && xc.q != DQUOTED)
		return (TRUE);
	return (FALSE);
}

static void	rm_first_delims(t_list **xc_lst)
{
	t_list	*xc_node;
	t_list	*next_node;

	xc_node = *xc_lst;
	while (xc_node && is_delim(xc_get(xc_node)))
	{
		next_node = xc_node->nxt;
		lst_rm_one(xc_lst, xc_node, free);
		xc_node = next_node;
	}
	*xc_lst = xc_node;
}

static t_xtoken	pop_word(t_list **xc_lst)
{
	t_list		*xc;
	t_xtoken	xtok;

	rm_first_delims(xc_lst);
	xtok.val = NULL;
	xtok.type = WORD;
	if (!*xc_lst)
		return (xtok);
	xc = *xc_lst;
	while (xc && !is_delim(xc_get(xc)))
	{
		xtok_addxc(&xtok, xc_get(xc));
		xc = xc->nxt;
	}
	lst_rm_many(xc_lst, *xc_lst, lst_size(xtok.val), free);
	return (xtok);
}

static void	split_words_xtok(t_list **xtokens, t_list **xtoken)
{
	t_xtoken	split_word;
	t_list		*split_words;
	t_list		*next_node;
	t_xtoken	*xtok_orig;

	xtok_orig = xtok_get(*xtoken);
	next_node = (*xtoken)->nxt;
	split_words = NULL;
	split_word = pop_word(&xtok_orig->val);
	while (split_word.val)
	{
		lst_add(&split_words, lst_new(&split_word, sizeof(split_word)));
		split_word = pop_word(&xtok_orig->val);
	}
	lst_rm_one(xtokens, *xtoken, free);
	lst_add_many(xtokens, next_node, split_words);
	*xtoken = next_node;
}

void	split_words(t_list **xtokens)
{
	t_list		*node;

	node = *xtokens;
	while (node)
	{
		if (xtok_get(node)->type == WORD)
			split_words_xtok(xtokens, &node);
		else
			node = node->nxt;
	}
}
