/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:33:57 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:23:52 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Returns TRUE if 'c' is the char <space> or <tab>, returns FALSE otherwise.
int	is_blankchr(int c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

// Returns TRUE if 'c' is the char '<' or '>', returns FALSE otherwise.
int	is_redirectionchr(int c)
{
	if (c == '<' || c == '>')
		return (TRUE);
	return (FALSE);
}

// Returns TRUE if 'c' is the char '<', '>' or '|', returns FALSE otherwise.
int	is_operatorchr(int c)
{
	if (is_redirectionchr(c) || c == '|')
		return (TRUE);
	return (FALSE);
}

// Returns TRUE if 'c' is the char <space>, <tab>, '<', '>' or '|', 
// returns FALSE otherwise.
int	is_metachr(int c)
{
	if (c == ' ' || c == '\t' || is_operatorchr(c))
		return (TRUE);
	return (FALSE);
}

// Returns TRUE if 'c' is the char ' or ", returns FALSE otherwise.
int	is_quotechr(int c)
{
	if (c == '\'' || c == '"')
		return (TRUE);
	return (FALSE);
}
