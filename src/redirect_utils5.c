/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:56:31 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 12:20:01 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <fcntl.h>
#include <unistd.h>

// Links the 'n'-th command's here document to the standard input.
// Returns the appropriate exit code after printing any error message.
int	link_heredoc(int n)
{
	char	*filename;
	int		fd_file;
	int		err;

	filename = heredoc_filename(n);
	fd_file = open_file(filename, O_RDONLY);
	free(filename);
	if (fd_file == -1)
		return (EXIT_FAILURE);
	err = dup2(fd_file, STDIN_FILENO);
	if (!err)
		err = close(fd_file);
	if (err)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// Executes the command 'cmd' (which might be a builtin) assuming there are no
// redirections and exits with the appropriate exit status.
void	execute_command(t_list *cmd, int exit_status, char **env)
{
	int		exit_stat;
	char	**args;
	char	**e;

	set_signals(NON_INTER);
	if (tok_get(cmd)->type == NULL_TOK)
		exit(EXIT_SUCCESS);
	args = get_args_from_cmd(cmd);
	if (is_builtin_name(args[0]))
	{
		e = arrstr_dup(env);
		exit_stat = exec_builtin(args, exit_status, &e, TRUE);
		arrstr_free(e);
		exit(exit_stat);
	}
	exec_cmd(args, env);
	exit(EXIT_FAILURE);
}

// Allocates and returns a NULL-terminated array of strings representing the
// list of tokens 'cmd'.
char	**get_args_from_cmd(t_list *cmd)
{
	char	**args;
	size_t	len;
	t_token	*tok;
	int		i;

	len = lst_size(cmd);
	args = (char **)p_malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (cmd)
	{
		tok = tok_get(cmd);
		args[i++] = ft_strdup(tok->val);
		cmd = cmd->nxt;
	}
	args[i] = NULL;
	return (args);
}

// Removes the temporary here document files, up to the 'n'-th command.
void	clear_heredocs(int n)
{
	char	*filename;

	while (n-- >= 0)
	{
		filename = heredoc_filename(n);
		unlink(filename);
		free(filename);
	}
}
