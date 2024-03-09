/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:08:41 by ydunay            #+#    #+#             */
/*   Updated: 2024/02/17 19:06:39 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Prints an error message when trying to execute a null command.
void	print_err_cmd_not_found(const char *cmdname)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmdname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(MSG_CMD_NOT_FOUND, STDERR_FILENO);
}

// Prints the error message for when trying to execute a command using an
// unset PATH variable.
void	print_err_nofile(const char *cmdname)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmdname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(MSG_NOFILE, STDERR_FILENO);
}

// Prints an error message when the given path is a directory.
void	print_err_isdir(const char *path)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(MSG_IS_DIR, STDERR_FILENO);
}

// Prints the corresponding execution error message (according to errno).
void	print_err_exec(const char *cmdname)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmdname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errno == ENOENT)
		ft_putendl_fd(MSG_CMD_NOT_FOUND, STDERR_FILENO);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

// Prints the corresponding filename error message (according to errno).
void	print_err_filename(const char *filename)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}
