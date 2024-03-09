/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xtoken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:53:08 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:16:04 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Given a xtoken list 'node' returns a pointer to its 'xtoken' value.
t_xtoken	*xtok_get(t_list *node)
{
	if (!node)
		return (NULL);
	return ((t_xtoken *)node->val);
}

// Adds 'xc' at the end of 'xtok'.
void	xtok_addxc(t_xtoken *xtok, t_xchar xc)
{
	lst_add(&(xtok->val), lst_new(&xc, sizeof(xc)));
}

// Returns an integer greater than, equal to, or less than 0, according as the
// string the value of 'xtok' is greater than, equal to, or less than 'str',
// comparing not more than 'n' characters.
int	xtok_strncmp(t_xtoken *xtok, const char *str, size_t n)
{
	int		ret;
	char	*xtok_val;

	xtok_val = xclst_to_str(xtok->val);
	ret = ft_strncmp(xtok_val, str, n);
	free(xtok_val);
	return (ret);
}

// Allocates and returns a string representing the given list of xchars 'xclst'.
char	*xclst_to_str(t_list *xclst)
{
	char	*str;
	size_t	str_len;
	t_xchar	xc;
	int		i;

	str_len = lst_size(xclst);
	str = (char *)p_malloc(sizeof(char) * (str_len + 1));
	i = -1;
	while (xclst && xclst->val)
	{
		xc = *(t_xchar *)(xclst->val);
		str[++i] = xc.c;
		xclst = xclst->nxt;
	}
	str[i + 1] = '\0';
	return (str);
}

// Converts the given xtoken to a token, losing the xchar flags and keeping the
// token type.
t_token	xtok_to_tok(t_xtoken *xtok)
{
	t_token	tok;

	tok.type = xtok->type;
	tok.val = xclst_to_str(xtok->val);
	return (tok);
}
