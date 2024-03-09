/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:08:41 by ydunay            #+#    #+#             */
/*   Updated: 2024/02/17 19:06:39 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

int	print_err_builtin(const char *builtin, const char *arg)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(builtin, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd("'", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
	}
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	print_err_too_many_arg(void)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putendl_fd(": exit: too many arguments", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	print_err_identifier(const char *builtin, const char *identifier)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(builtin, STDERR_FILENO);
	ft_putstr_fd(": '", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putendl_fd(MSG_IDENTERR, STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	print_err_numeric_arg(const char *arg)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putstr_fd(": exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(MSG_NUMARG, STDERR_FILENO);
	return (EXIT_NUMARG);
}

// Prints an error message when user is not allowed to execute 'cmdname'.
void	print_err_perm_denied(const char *cmdname)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmdname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(MSG_PERM_DENIED, STDERR_FILENO);
}
