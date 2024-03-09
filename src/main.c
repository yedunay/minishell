/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:50:24 by ydunay            #+#    #+#             */
/*   Updated: 2024/02/17 18:43:57 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **e)
{
	char	**env;

	if (ac != 1)
		return (print_err_argc());
	av += 0;
	env = arrstr_dup(e);
	minish_loop(env);
	return (EXIT_FAILURE);
}
