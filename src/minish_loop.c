/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:18:05 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:53:42 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <signal.h>
#include <unistd.h>

static void	force_exit(int exit_status)
{
	if (isatty(STDOUT_FILENO))
		ft_putendl_fd("\033[A\033[2Kminish$ exit", STDERR_FILENO);
	restore_exit(exit_status);
}

static int	control_and_c(int exit_status)
{
	if (g_signal == SIGINT)
		exit_status = EXIT_FAILURE;
	signal(SIGINT, SIG_IGN);
	return (exit_status);
}

// Frees an array of commands (as a list of tokens).
static void	free_commands(t_list **commands)
{
	int	i;

	i = -1;
	while (commands[++i])
		lst_clear(&commands[i], tok_del);
	free(commands);
}

// Returns TRUE if there are no 'commands', freeing the referenced
// 'commands' array of commands if needed.
static int	not_commands(t_list	**commands)
{
	if (!commands)
		return (TRUE);
	if (!*commands)
	{
		free_commands(commands);
		return (TRUE);
	}
	return (FALSE);
}

void	minish_loop(char **env)
{
	char	*input;
	t_list	*tokens;
	t_list	**commands;
	int		exit_status;

	exit_status = 0;
	while (42)
	{
		set_signals(INTER);
		input = get_input();
		exit_status = control_and_c(exit_status);
		if (!input)
			force_exit(exit_status);
		tokens = tokenize(input);
		free(input);
		commands = parse(tokens, &exit_status);
		lst_clear(&tokens, tok_del);
		if (not_commands(commands))
			continue ;
		commands = expand_and_split(commands, exit_status, env);
		redirect_and_execute(commands, &exit_status, &env);
		free_commands(commands);
	}
}
