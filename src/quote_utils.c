/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:39:26 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:20:07 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Given the current quote status and a character 'c', updates its value and
// returns the status for 'c'.
int	quote_stat(int *curr_stat, char c)
{
	if (c == '"')
	{
		if (*curr_stat == DQUOTED)
			*curr_stat = UNQUOTED;
		else if (*curr_stat == UNQUOTED)
		{
			*curr_stat = DQUOTED;
			return (UNQUOTED);
		}
	}
	else if (c == '\'')
	{
		if (*curr_stat == QUOTED)
			*curr_stat = UNQUOTED;
		else if (*curr_stat == UNQUOTED)
		{
			*curr_stat = QUOTED;
			return (UNQUOTED);
		}
	}
	return (*curr_stat);
}

// Removes all unquoted ocurrences of ' and " that didn't result form expansion.
static void	remove_quotes_xtok(t_xtoken *xtok)
{
	t_xchar	quote;
	t_xchar	dquote;

	if (xtok->type != WORD)
		return ;
	quote = xc_new('\'', UNEXPANDED, UNQUOTED);
	dquote = xc_new('"', UNEXPANDED, UNQUOTED);
	xtok_rm_xcs(xtok, &quote);
	xtok_rm_xcs(xtok, &dquote);
}

// For each word on the 'xtokens' list, removes all unquoted ocurrences of 
// ' and " that didn't result form expansion (excluding those after << redirs).
void	remove_quotes(t_list *xtokens)
{
	t_xtoken	*xtok;
	t_list		*node;
	int			skip_next;

	skip_next = FALSE;
	node = xtokens;
	while (node)
	{
		xtok = xtok_get(node);
		if (xtok->type == WORD)
		{
			if (skip_next)
				skip_next = FALSE;
			else
				remove_quotes_xtok(xtok);
		}
		else if (!xtok_strncmp(xtok, "<<", 3))
			skip_next = TRUE;
		node = node->nxt;
	}
}
