/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:31:21 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:18:49 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Given that 'varname' points to the first character of a variable name,
// returns its value. If 'varname' does not exist, returns NULL.
char	*env_get_var(const char *varname, char **env)
{
	int		name_len;
	char	*var_line;

	var_line = env_find_var_line(varname, env);
	name_len = env_name_len(varname);
	if (var_line == NULL)
		return (NULL);
	return (var_line + name_len + 1);
}

// Given that 'str' points to the first character of a variable name,
// returns its length.
int	env_name_len(const char *str)
{
	int	i;

	i = 0;
	if (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
	{
		++i;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			++i;
	}
	return (i);
}

// Returns a pointer to the first character of the line containing the
// environment variable 'varname'. If 'varname' is not found returns NULL.
char	*env_find_var_line(const char *varname, char **env)
{
	int	name_len;

	name_len = env_name_len(varname);
	if (name_len == 0)
		return (NULL);
	while (*env)
	{
		if (!ft_strncmp(*env, varname, name_len) && (*env)[name_len]
			&& (*env)[name_len] == '=')
			return ((char *)*env);
		++env;
	}
	return (NULL);
}

// Returns the index of the environment variable 'varname'.
// If 'varname' is not found, returns -1.
int	env_find_var_index(const char *varname, char **env)
{
	int	name_len;
	int	i;

	name_len = env_name_len(varname);
	if (name_len == 0)
		return (-1);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], varname, name_len) == 0)
			return (i);
	}
	return (-1);
}

// Check if the string has a proper name for an environment variable before
// any '=' if exists.
// Allocates and returns the valid varname or NULL if invalid.
char	*env_get_varname(const char *str)
{
	int		len;
	char	*varname;

	if (!str)
		return (NULL);
	if (!ft_strchr(str, '='))
		len = ft_strlen(str);
	else
		len = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
	varname = ft_strdup(str);
	varname[len] = '\0';
	if (!env_valid_varname(varname))
	{
		free(varname);
		return (NULL);
	}
	return (varname);
}
