/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:36:31 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:19:17 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/stat.h>
#include <unistd.h>

int	path_exists(const char *path)
{
	if (access(path, F_OK) == -1)
		return (FALSE);
	return (TRUE);
}

int	is_directory(const char *path)
{
	struct stat	stats;

	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
		return (TRUE);
	return (FALSE);
}

int	can_execute(const char *path)
{
	if (access(path, X_OK) == -1)
		return (FALSE);
	return (TRUE);
}

int	wait_children(pid_t last_pid, size_t n)
{
	pid_t	pid;
	size_t	i;
	int		status;
	int		ret_status;

	i = 0;
	while (i++ < n)
	{
		pid = wait(&status);
		if (pid == last_pid)
			ret_status = status;
	}
	if (WIFEXITED(ret_status))
		return (WEXITSTATUS(ret_status));
	else if (WIFSIGNALED(ret_status))
	{
		if (WTERMSIG(ret_status) == SIGQUIT)
			ft_putstr_fd("Quit: 3", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (WTERMSIG(ret_status) + 128);
	}
	return (EXIT_FAILURE);
}

int	execute_builtin(t_list *cmd, int exit_status, char ***env, int child)
{
	char	**args;
	int		exit_stat;

	args = get_args_from_cmd(cmd);
	exit_stat = exec_builtin(args, exit_status, env, child);
	arrstr_free(args);
	return (exit_stat);
}
