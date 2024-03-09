/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xtoken3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:56:16 by ydunay            #+#    #+#             */
/*   Updated: 2024/02/17 18:43:37 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Removes all ocurrences of 'to_rm' from the given xtoken.
void	xtok_rm_xcs(t_xtoken *xtok, t_xchar *to_rm)
{
	t_xchar	xc;
	t_list	*curr_node;
	t_list	*next_node;

	curr_node = xtok->val;
	while (curr_node)
	{
		xc = *(t_xchar *)curr_node->val;
		next_node = curr_node->nxt;
		if (xc.c == to_rm->c && xc.q == to_rm->q && xc.x == to_rm->x)
		{
			if (xtok->val == curr_node)
				xtok->val = next_node;
			xtok_rm_one(xtok, curr_node);
		}
		curr_node = next_node;
	}
}

// Converts the given token to a xtoken, keeping the token type and setting the
// appropriate xchar flags.
t_xtoken	tok_to_xtok(t_token *tok)
{
	t_xtoken	xtok;
	char		*str;
	int			q_stat;
	int			char_stat;

	xtok.type = tok->type;
	xtok.val = NULL;
	q_stat = UNQUOTED;
	str = tok->val;
	while (*str)
	{
		char_stat = quote_stat(&q_stat, *str);
		xtok_addc(&xtok, *str, UNEXPANDED, char_stat);
		++str;
	}
	return (xtok);
}
