/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:02:08 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:18:29 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

static void	end_in_slash(char **path)
{
	if ((*path)[ft_strlen(*path)] != '/')
		ft_strjoin_free(path, "/");
}

static int	is_relativepath(char *str)
{
	if (str[0] != '/')
		return (TRUE);
	return (FALSE);
}

static int	is_same_or_parent_dir(char *str)
{
	if (str[0] != '.')
		return (FALSE);
	if (str[1] == '\0' || str[1] == '/')
		return (TRUE);
	if (str[1] == '.' && (str[2] == '\0' || str[2] == '/'))
		return (TRUE);
	return (FALSE);
}

static int	try_cdpath(char *str, char **env)
{
	char	**path;
	int		i;

	i = -1;
	path = env_get_vars("CDPATH", env);
	if (path == NULL)
		return (FALSE);
	while (path[++i])
	{
		end_in_slash(&path[i]);
		ft_strjoin_free(&path[i], str);
		if (chdir(path[i]) == 0)
		{
			arrstr_free(path);
			return (TRUE);
		}
	}
	arrstr_free(path);
	return (FALSE);
}

int	cd_builtin(char **args, char **env)
{
	if (*args == NULL)
	{
		if (chdir(env_get_var("HOME", env)) < 0)
			return (print_err_builtin("cd", *args));
		return (EXIT_SUCCESS);
	}
	if (**args == '\0')
		return (EXIT_SUCCESS);
	if (is_relativepath(*args) && is_same_or_parent_dir(*args) == FALSE)
	{
		if (try_cdpath(*args, env))
			return (pwd_builtin());
	}
	if (chdir(*args) < 0)
		return (print_err_builtin("cd", *args));
	return (EXIT_SUCCESS);
}
