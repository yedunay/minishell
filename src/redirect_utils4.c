/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:50:02 by ydunay            #+#    #+#             */
/*   Updated: 2024/02/24 17:06:38 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>
#include <fcntl.h>

// Performs all redirections of 'cmd', from left-to-right, removing the
// redirection tokens, knowing it's the 'n'-th command. Returns the exit status.
// If a redirection error ocurrs, prints an error message.
static int	redirect_one(char *redir, t_list *next, int n);

int	redirect(t_list **cmd, int n)
{
	int		exit_stat;
	t_list	*node;
	t_list	*nxt_node;
	t_token	*tok;

	exit_stat = 0;
	node = *cmd;
	while (node && exit_stat == 0)
	{
		tok = tok_get(node);
		if (tok->type == REDIR)
		{
			exit_stat = redirect_one(tok->val, node->nxt, n);
			nxt_node = lst_move(node, 2);
			lst_rm_many(cmd, node, 2, tok_del);
			node = nxt_node;
		}
		else
			node = node->nxt;
	}
	return (exit_stat);
}

// Performs the redirection defined by 'redir', taking 'next' as the following 
// token, knowing it's the 'n'-th command.
// In the case of here documents, quote-removal is performed.
// Returns the appropriate exit code after printing any error message.
static int	redirect_one(char *redir, t_list *next, int n)
{
	char	*str;

	if (!next)
	{
		print_err_redir();
		return (EXIT_AMBIG_REDIR);
	}
	str = tok_get(next)->val;
	if (!ft_strncmp(redir, ">", 2))
		return (link_output_file(str, FALSE));
	else if (!ft_strncmp(redir, ">>", 3))
		return (link_output_file(str, TRUE));
	else if (!ft_strncmp(redir, "<", 2))
		return (link_input_file(str));
	else if (!ft_strncmp(redir, "<<", 3))
		return (link_heredoc(n));
	return (EXIT_FAILURE);
}

// Opens the file 'filename' and links it to the standard output.
// If 'append' is not zero, it opens the file with the O_APPEND flag.
// Returns the appropriate exit code after printing any error message.
int	link_output_file(const char *filename, int append)
{
	int	fd_file;
	int	flags;
	int	ret;

	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd_file = open_file(filename, flags);
	if (fd_file == -1)
		return (EXIT_FAILURE);
	ret = dup2(fd_file, STDOUT_FILENO);
	if (ret == -1)
		return (EXIT_FAILURE);
	ret = close(fd_file);
	if (ret == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// Opens the file 'filename' with the 'flags' and returns its file descriptor.
// On failure, prints an error message and returns -1 (setting errno).
int	open_file(const char *filename, int flags)
{
	int	fd_file;

	fd_file = open(filename, flags, OPEN_FILE_MODE);
	if (fd_file == -1)
		print_err_filename(filename);
	return (fd_file);
}

// Opens the file 'filename' and links it to the standard input.
// Returns the appropriate exit code after printing any error message.
int	link_input_file(const char *filename)
{
	int	fd_file;
	int	ret;

	fd_file = open_file(filename, O_RDONLY);
	if (fd_file == -1)
		return (EXIT_FAILURE);
	ret = dup2(fd_file, STDIN_FILENO);
	if (ret == -1)
		return (EXIT_FAILURE);
	ret = close(fd_file);
	if (ret == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
