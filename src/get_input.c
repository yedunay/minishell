/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:26:25 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:23:55 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// Prints the prompt and waits for user input (managing the history).
// Allocates and returns the string provided by the user.
char	*get_input(void)
{
	char	*str;

	str = readline("minish % ");
	if (str && *str)
		add_history(str);
	return (str);
}
