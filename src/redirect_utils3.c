/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:38:26 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:17:31 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

void	pipe_or_die(int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
	{
		print_err_pipe();
		exit (EXIT_PIPE_ERR);
	}
}

pid_t	fork_or_die(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);
	return (pid);
}

int	process_command(t_pipe *p, t_list *cmd, int e_stat, char **env)
{
	int		exit_stat;

	if (p->i > 0)
		link_read_end(p->prev_fds);
	if (p->i < p->cmds_amount - 1)
		link_write_end(p->next_fds);
	exit_stat = redirect(&cmd, p->i);
	if (exit_stat != 0)
		exit(exit_stat);
	if (lst_size(cmd) == 0)
		exit(EXIT_SUCCESS);
	execute_command(cmd, e_stat, env);
	return (EXIT_FAILURE);
}

void	link_read_end(int *fd_pipe)
{
	close(fd_pipe[WRITE_END]);
	dup2(fd_pipe[READ_END], STDIN_FILENO);
	close(fd_pipe[READ_END]);
}

void	link_write_end(int *fd_pipe)
{
	close(fd_pipe[READ_END]);
	dup2(fd_pipe[WRITE_END], STDOUT_FILENO);
	close(fd_pipe[WRITE_END]);
}
