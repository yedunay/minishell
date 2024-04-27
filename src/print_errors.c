/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:03:25 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 12:11:52 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../inc/minishell.h"
#include <errno.h>
#include <string.h>

int	print_err_argc(void)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(MSG_WRONGAC, STDERR_FILENO);
	return (EXIT_WRONGAC);
}

int	print_err_syntax(const char *token, int ret)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(MSG_SYNTERR, STDERR_FILENO);
	ft_putstr_fd(" '", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (ret);
}

int	print_err_heredoc(int ret)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(MSG_HEREDOC_ERR, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (ret);
}

void	print_err_pipe(void)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(MSG_PIPE_ERR, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	print_err_redir(void)
{
	ft_putstr_fd("minish % ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(MSG_AMBIG_REDIR, STDERR_FILENO);
}
