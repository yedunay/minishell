/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:18:27 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:47:17 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

static void	printvar_quoted(const char *var)
{
	while (*var != '=')
	{
		write(1, var, 1);
		++var;
	}
	write(1, "=\"", 2);
	++var;
	while (*var)
	{
		write(1, var, 1);
		++var;
	}
	write(1, "\"\n", 2);
}

static int	export_noargs(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			printvar_quoted(env[i]);
		}
		else if (!ft_strchr(env[i], '='))
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(env[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
	return (0);
}

int	export_builtin(char **args, char ***env, int exit_status)
{
	char	*varname;
	int		i;

	if (!*args--)
		return (export_noargs(*env));
	while (++args && *args)
	{
		i = 0;
		varname = env_get_varname(*args);
		if (!env_valid_varname(varname))
		{
			exit_status = print_err_identifier("export", *args);
			free(varname);
			continue ;
		}
		while ((*args)[i] && (*args)[i] != '=')
			++i;
		if ((*args)[i++] == '=')
			env_set_var(varname, (*args) + i, env, 1);
		else
			env_set_var(varname, "", env, 0);
		free(varname);
	}
	return (exit_status);
}

static char	*join_varline(const char *varname, const char *value, int fl)
{
	char	*varline;
	size_t	varline_len;
	int		i;

	varline_len = ft_strlen(varname) + ft_strlen(value) + 1;
	varline = (char *)p_malloc(sizeof(char) * (varline_len + 1));
	i = 0;
	while (*varname)
		varline[i++] = *varname++;
	if (fl)
		varline[i++] = '=';
	while (*value)
		varline[i++] = *value++;
	varline[i] = '\0';
	return (varline);
}

void	env_set_var(const char *varname, const char *value, char ***env, int fl)
{
	int		var_index;
	char	*varline;

	varline = join_varline(varname, value, fl);
	var_index = env_find_var_index(varname, (char **)*env);
	if (var_index == -1)
		*env = arrstr_add(*env, varline);
	else
		*env = arrstr_set(*env, varline, var_index);
	free(varline);
}
