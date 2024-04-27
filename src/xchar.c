/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:54:15 by ydunay            #+#    #+#             */
/*   Updated: 2024/02/17 18:43:37 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_xchar	xc_get(t_list *node)
{
	t_xchar	xc;

	xc = *(t_xchar *)node->val;
	return (xc);
}

t_xchar	xc_new(char c, int x_flag, int q_flag)
{
	t_xchar	xc;

	xc.c = c;
	xc.x = x_flag;
	xc.q = q_flag;
	return (xc);
}

t_list	*str_to_xclst(const char *str, int x_flag, int q_flag)
{
	t_list	*lst;
	t_xchar	xc;

	lst = NULL;
	while (str && *str)
	{
		xc.c = *str;
		xc.x = x_flag;
		xc.q = q_flag;
		lst_add(&lst, lst_new(&xc, sizeof(xc)));
		++str;
	}
	return (lst);
}
