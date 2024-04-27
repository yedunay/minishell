/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:05:05 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 12:13:50 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

static int	process_builtin_here(t_list **cmd, int exit_status, char ***env)
{
	int	exit_stat;

	save_restore_stdio(STDIN_FILENO, STDOUT_FILENO, SAVE);
	exit_stat = read_heredocs(*cmd, 0, *env);
	if (exit_stat)
		return (exit_stat);
	exit_stat = redirect(cmd, 0);
	if (exit_stat != 0)
	{
		save_restore_stdio(STDIN_FILENO, STDOUT_FILENO, RESTORE);
		return (exit_stat);
	}
	if (lst_size(*cmd) > 0)
		exit_stat = execute_builtin(*cmd, exit_status, env, FALSE);
	save_restore_stdio(STDIN_FILENO, STDOUT_FILENO, RESTORE);
	return (exit_stat);
}

int	read_all_heredocs(t_list **cmds, int cmds_amount, char **env)
{
	int		i;
	int		ret;

	stop_signals();
	i = -1;
	while (++i < cmds_amount)
	{
		ret = read_heredocs(cmds[i], i, env);
		if (ret)
			return (ret);
	}
	return (0);
}

static void	parent_pipe_update(t_pipe *p, int i)
{
	if (i > 0)
	{
		close(p->prev_fds[READ_END]);
		close(p->prev_fds[WRITE_END]);
	}
	if (i < p->cmds_amount - 1)
	{
		p->prev_fds[READ_END] = p->next_fds[READ_END];
		p->prev_fds[WRITE_END] = p->next_fds[WRITE_END];
	}
}

static int	process_commands(t_list **cmds, t_pipe *p, int e_stat, char **env)
{
	int		exit_stat;
	int		i;
	pid_t	pid;
	pid_t	last_child;

	exit_stat = read_all_heredocs(cmds, p->cmds_amount, env);
	if (exit_stat)
		return (exit_stat);
	stop_signals();
	i = -1;
	while (++i < p->cmds_amount)
	{
		p->i = i;
		if (i < p->cmds_amount - 1)
			pipe_or_die(p->next_fds);
		pid = fork_or_die();
		if (pid == 0)
			return (process_command(p, cmds[i], e_stat, env));
		parent_pipe_update(p, i);
		last_child = pid;
	}
	exit_stat = wait_children(last_child, p->cmds_amount);
	clear_heredocs(p->cmds_amount);
	return (exit_stat);
}

void	redirect_and_execute(t_list **commands, int *exit_status, char ***env)
{
	t_pipe	p;

	p.cmds_amount = arr_size((void *)commands);
	if (p.cmds_amount == 0)
		*exit_status = 0;
	else if (p.cmds_amount == 1 && is_builtin_cmd(commands[0]))
		*exit_status = process_builtin_here(commands, *exit_status, env);
	else
		*exit_status = process_commands(commands, &p, *exit_status, *env);
}
