/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:13:41 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 12:06:29 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

static int	is_flag(char *word)
{
	int	i;

	i = 0;
	if (word[i++] != '-')
		return (FALSE);
	while (word[i] && word[i] == 'n')
		++i;
	if (word[i])
		return (FALSE);
	return (TRUE);
}

static int	get_flag(char **args)
{
	int	idx;

	idx = 0;
	while (args[idx] && is_flag(args[idx]))
		++idx;
	return (idx);
}

// Output the 'args', separated by spaces, followed by a newline.
// The return status is always 0.
// If -n is specified, the trailing newline is suppressed.
int	echo_builtin(char **args)
{
	int	first;
	int	flag;

	first = 0;
	flag = get_flag(args);
	args += flag;
	while (*args)
	{
		if (first)
			printf(" ");
		printf("%s", *args);
		first = 1;
		args++;
	}
	if (!flag)
		printf("\n");
	return (0);
}
