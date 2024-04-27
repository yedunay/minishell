/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:49:50 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:42:09 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_list	*expand_and_split_cmd(t_list *cmd, int exit_status, char **env)
{
	t_list	*new_cmd;
	t_list	*xtoks;

	xtoks = expand(cmd, exit_status, env);
	lst_clear(&cmd, tok_del);
	split_words(&xtoks);
	remove_quotes(xtoks);
	new_cmd = normalize(xtoks);
	xtoklst_clear(&xtoks);
	return (new_cmd);
}

t_list	**expand_and_split(t_list **commands, int exit_status, char **env)
{
	int		i;
	t_token	tok;

	i = -1;
	while (commands[++i])
	{
		commands[i] = expand_and_split_cmd(commands[i], exit_status, env);
		if (commands[i] == NULL)
		{
			tok = tok_create_null();
			commands[i] = lst_new(&tok, sizeof(t_token));
		}
	}
	return (commands);
}

void	lst_add_many(t_list **lst, t_list *pos, t_list *to_add)
{
	t_list	*prev;
	t_list	*next;

	if (!to_add)
		return ;
	if (!*lst)
	{
		*lst = to_add;
		return ;
	}
	if (!pos)
	{
		prev = lst_last(*lst);
		next = NULL;
	}
	else
	{
		prev = pos->pre;
		next = pos;
	}
	lst_link(prev, to_add);
	lst_link(lst_last(to_add), next);
	if (!prev)
		*lst = to_add;
}

t_list	*normalize(t_list *xtokens)
{
	t_list	*cmd;
	t_list	*xtok;
	t_token	tok;
	t_list	*new_tok;

	cmd = NULL;
	xtok = xtokens;
	while (xtok)
	{
		tok = xtok_to_tok(xtok->val);
		new_tok = lst_new(&tok, sizeof(tok));
		lst_add(&cmd, new_tok);
		xtok = xtok->nxt;
	}
	return (cmd);
}
