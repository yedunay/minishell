/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:36:52 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:17:06 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	tok_type(const char *str)
{
	if (!str)
		return (INVALID);
	if (ft_strncmp(str, ">", 2) == 0 || ft_strncmp(str, "<", 2) == 0
		|| ft_strncmp(str, "<<", 3) == 0 || ft_strncmp(str, ">>", 3) == 0)
		return (REDIR);
	if (ft_strncmp(str, "|", 2) == 0)
		return (PIPE);
	if (is_word(str))
		return (WORD);
	return (INVALID);
}

t_token	tok_create(const char *str)
{
	t_token	token;

	token.val = ft_strdup(str);
	token.type = tok_type(str);
	return (token);
}

t_token	tok_create_null(void)
{
	t_token	token;

	token.val = ft_strdup("");
	token.type = NULL_TOK;
	return (token);
}

void	tok_del(void *token)
{
	free(((t_token *)token)->val);
	free(token);
}

t_token	*tok_get(t_list *node)
{
	if (!node)
		return (NULL);
	return ((t_token *)node->val);
}
