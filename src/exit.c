/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:15:31 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 12:08:41 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

static int	ft_check_llong(char *arg)
{
	int		len;
	int		diff;
	char	sign;

	sign = '+';
	if (*arg == '-' || *arg == '+')
	{
		sign = *arg;
		arg++;
	}
	while (*arg == '0')
		arg++;
	len = ft_strlen(arg);
	if (len > 19)
		return (FALSE);
	if (len == 19)
	{
		if (sign == '-')
			diff = ft_strncmp(arg, LLINT_MIN_STR, 19);
		else
			diff = ft_strncmp(arg, LLINT_MAX_STR, 19);
		if (diff > 0)
			return (FALSE);
	}
	return (TRUE);
}

static int	is_longlong(char *arg)
{
	int	i;

	i = 0;
	if (!*arg)
		return (FALSE);
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i + 1] == 0)
			return (FALSE);
		++i;
	}
	while (arg[i] == '0')
		++i;
	while (arg[i] && ((arg[i] <= '9' && arg[i] >= '0')))
		++i;
	if (arg[i])
		return (FALSE);
	return (ft_check_llong(arg));
}

int	exit_builtin(char **args, int exit_status, int is_child)
{
	long long	exit_stat;
	char		*str;

	if (!is_child)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (*args == NULL)
		restore_exit(exit_status);
	str = ft_strtrim(args[0], " \n\t\v\f\r");
	if (is_longlong(str) == FALSE)
	{
		free(str);
		restore_exit(print_err_numeric_arg(args[0]));
	}
	if (args[1] == NULL)
	{
		exit_stat = ft_atoll(str);
		free(str);
		restore_exit(exit_stat % 256);
	}
	free(str);
	return (print_err_too_many_arg());
}
