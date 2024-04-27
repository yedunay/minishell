/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:23:52 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:19:05 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	env_valid_varname(char *word)
{
	if (!word || !*word)
		return (FALSE);
	if (*word == '_' || ft_isalpha(*word))
	{
		++word;
		while (*word == '_' || ft_isalnum(*word))
			++word;
	}
	if (!*word)
		return (TRUE);
	return (FALSE);
}

char	**arrstr_rm(char **arr, int i)
{
	char	**orig_arr;
	char	**new_arr;
	int		orig_arr_size;
	int		j;

	orig_arr = arr;
	orig_arr_size = arrstr_size(orig_arr);
	new_arr = (char **)p_malloc(sizeof(char *) * orig_arr_size);
	j = -1;
	while (++j < i)
		new_arr[j] = ft_strdup(orig_arr[j]);
	while (orig_arr[j + 1])
	{
		new_arr[j] = ft_strdup(orig_arr[j + 1]);
		++j;
	}
	new_arr[j] = NULL;
	arrstr_free(arr);
	return (new_arr);
}

void	env_rm_var(const char *varname, char ***env)
{
	int	var_index;

	var_index = env_find_var_index(varname, *env);
	if (var_index >= 0)
		*env = arrstr_rm(*env, var_index);
}

int	unset_builtin(char **args, char ***env)
{
	int	i;
	int	ret_status;

	i = -1;
	ret_status = 0;
	while (args[++i])
	{
		if (env_valid_varname(args[i]))
			env_rm_var(args[i], env);
		else
			ret_status = print_err_identifier("unset", args[i]);
	}
	return (ret_status);
}
