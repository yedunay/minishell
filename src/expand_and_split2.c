/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_split2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:49:50 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:43:14 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	expand_var(t_list **lst, t_list **node, char **env)
{
	char	*name;
	char	*value;
	int		len;
	t_list	*expanded_lst;

	*node = (*node)->nxt;
	name = xclst_to_str(*node);
	value = env_get_var(name, env);
	expanded_lst = str_to_xclst(value, EXPANDED, xc_get(*node).q);
	lst_add_many(lst, (*node)->pre, expanded_lst);
	len = env_name_len(name);
	free(name);
	*node = lst_move(*node, len);
	if (!*node)
		lst_rm_many(lst, lst_move(lst_last(*lst), -(len)), len + 1, free);
	else
		lst_rm_many(lst, lst_move(*node, -(len + 1)), len + 1, free);
}

static void	expand_exit_stat(t_list **lst, t_list **node, int exit_status)
{
	char	*value;
	t_list	*expanded_lst;

	value = ft_itoa(exit_status);
	expanded_lst = str_to_xclst(value, EXPANDED, xc_get(*node).q);
	free(value);
	lst_add_many(lst, *node, expanded_lst);
	*node = lst_move(*node, 2);
	if (!*node)
		lst_rm_many(lst, lst_move(lst_last(*lst), -1), 2, free);
	else
		lst_rm_many(lst, lst_move(*node, -2), 2, free);
}

static int	try_to_expand(t_list *node)
{
	t_xchar	xc;
	t_xchar	xc_next;

	if (!node->nxt)
		return (FALSE);
	xc = xc_get(node);
	xc_next = xc_get(node->nxt);
	if (xc.q != QUOTED && xc.c == '$'
		&& (ft_isalpha(xc_next.c) || xc_next.c == '?' || xc_next.c == '_'))
		return (TRUE);
	return (FALSE);
}

static void	expand_xtok(t_xtoken *xtok, int exit_status, char **env)
{
	t_list	*node;

	if (xtok->type != WORD)
		return ;
	node = xtok->val;
	while (node && node->val)
	{
		if (try_to_expand(node))
		{
			if (((t_xchar *)((node->nxt)->val))->c == '?')
				expand_exit_stat(&(xtok->val), &node, exit_status);
			else
				expand_var(&(xtok->val), &node, env);
		}
		else
			node = node->nxt;
	}
}

t_list	*expand(t_list *toks, int exit_status, char **env)
{
	t_list		*xtoks;
	t_xtoken	xtok;
	t_list		*node;
	int			skip_next;

	skip_next = FALSE;
	xtoks = NULL;
	node = toks;
	while (node)
	{
		xtok = tok_to_xtok((t_token *)node->val);
		if (xtok.type == WORD)
		{
			if (skip_next)
				skip_next = FALSE;
			else
				expand_xtok(&xtok, exit_status, env);
		}
		else if (!xtok_strncmp(&xtok, "<<", 3))
			skip_next = TRUE;
		lst_add(&xtoks, lst_new(&xtok, sizeof(xtok)));
		node = node->nxt;
	}
	return (xtoks);
}
