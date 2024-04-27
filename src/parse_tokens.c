/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:43:02 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:23:24 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_valid_redir(t_list *node)
{
	t_token	*next_tok;

	if (node->nxt == NULL)
		return (FALSE);
	next_tok = tok_get(node->nxt);
	if (next_tok->type != WORD)
		return (FALSE);
	return (TRUE);
}

static int	is_valid_pipe(t_list *node)
{
	t_token	*prev_tok;
	t_token	*next_tok;

	if (node->pre == NULL || node->nxt == NULL)
		return (FALSE);
	next_tok = tok_get(node->nxt);
	prev_tok = tok_get(node->pre);
	if (prev_tok->type == WORD
		&& (next_tok->type == WORD || next_tok->type == REDIR))
		return (TRUE);
	else
		return (FALSE);
}

static int	count_commands_checking_syntax(t_list *tokens)
{
	int		cmd_amount;
	t_list	*node;
	t_token	*tok;

	cmd_amount = 1;
	node = tokens;
	while (node)
	{
		tok = tok_get(node);
		if (tok->type == INVALID)
			return (print_err_syntax(tok->val, -1));
		if (tok->type == REDIR && !is_valid_redir(node))
			return (print_err_syntax(tok->val, -1));
		if (tok->type == PIPE)
		{
			++cmd_amount;
			if (!is_valid_pipe(node))
				return (print_err_syntax(tok->val, -1));
		}
		node = node->nxt;
	}
	return (cmd_amount);
}

static void	add_cmd(t_list **cmd, t_list **node)
{
	t_list	*next_node;
	t_token	*tok;
	t_token	tok_copy;

	*cmd = NULL;
	while (*node)
	{
		tok = tok_get(*node);
		if (tok->type != PIPE)
		{
			tok_copy = tok_create(tok->val);
			lst_add(cmd, lst_new(&tok_copy, sizeof(tok_copy)));
		}
		else
		{
			next_node = (*node)->nxt;
			*node = next_node;
			return ;
		}
		*node = (*node)->nxt;
	}
	return ;
}

t_list	**parse(t_list *tokens, int *exit_status)
{
	int		cmd_amount;
	t_list	**cmds;
	int		i;
	t_list	*node;

	cmd_amount = count_commands_checking_syntax(tokens);
	if (cmd_amount == -1)
	{
		*exit_status = EXIT_SYNTERR;
		return (NULL);
	}
	cmds = (t_list **)p_malloc(sizeof(t_list *) * (cmd_amount + 1));
	i = -1;
	node = tokens;
	while (++i < cmd_amount)
	{
		add_cmd(&cmds[i], &node);
	}
	cmds[i] = NULL;
	return (cmds);
}
