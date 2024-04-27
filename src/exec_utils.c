/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:31:34 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 12:07:39 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

static void	check_path(const char *path)
{
	if (!path_exists(path))
	{
		print_err_nofile(path);
		exit(EXIT_NOFILE);
	}
	if (is_directory(path))
	{
		print_err_isdir(path);
		exit(EXIT_IS_DIR);
	}
	if (!can_execute(path))
	{
		print_err_perm_denied(path);
		exit(EXIT_PERM_DENIED);
	}
}

void	exec_cmd(char **cmd, char **env)
{
	char	**args;
	char	*path;

	path = cmd[0];
	args = cmd;
	if (!ft_strchr(path, '/'))
		path = get_executable(path, env);
	else
		check_path(path);
	execve(path, args, env);
	print_err_exec(cmd[0]);
	exit(EXIT_FAILURE);
}

static char	*get_full_path(const char *dir, const char *file)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	full_path = ft_strjoin(tmp, file);
	free(tmp);
	return (full_path);
}

char	*get_executable(const char *file, char **env)
{
	char	*path;
	char	**paths;
	int		i;

	paths = env_get_vars("PATH", env);
	i = -1;
	while (paths && paths[++i])
	{
		path = get_full_path(paths[i], file);
		if (path_exists(path) && !is_directory(path))
		{
			if (can_execute(path))
				return (path);
			else
			{
				free(path);
				print_err_perm_denied(file);
				exit(EXIT_PERM_DENIED);
			}
		}
		free(path);
	}
	print_err_cmd_not_found(file);
	exit(EXIT_CMD_NOT_FOUND);
}

char	**env_get_vars(const char *varname, char **env)
{
	char	*value;
	char	**values;

	value = env_get_var(varname, env);
	if (!value)
		return (NULL);
	values = ft_split(value, ':');
	return (values);
}
