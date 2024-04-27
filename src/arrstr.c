/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:03:27 by ydunay            #+#    #+#             */
/*   Updated: 2024/02/17 18:43:37 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**arrstr_dup(char **arr)
{
	char	**new_arr;
	int		orig_arr_size;
	int		i;

	orig_arr_size = arrstr_size(arr);
	new_arr = (char **)p_malloc(sizeof(char *) * (orig_arr_size + 1));
	i = -1;
	while (++i < orig_arr_size)
		new_arr[i] = ft_strdup(arr[i]);
	new_arr[i] = NULL;
	return (new_arr);
}

size_t	arrstr_size(char **arr)
{
	return (arr_size((void *)arr));
}

char	**arrstr_add(char **arr, const char *str)
{
	char	**new_arr;
	int		orig_arr_size;
	int		i;

	orig_arr_size = arrstr_size(arr);
	new_arr = (char **)p_malloc(sizeof(char *) * (orig_arr_size + 2));
	i = -1;
	while (++i < orig_arr_size)
		new_arr[i] = ft_strdup(arr[i]);
	new_arr[i] = ft_strdup(str);
	new_arr[i + 1] = NULL;
	arrstr_free(arr);
	return (new_arr);
}

char	**arrstr_set(char **arr, const char *str, int i)
{
	free(arr[i]);
	arr[i] = ft_strdup(str);
	return (arr);
}

void	arrstr_free(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*tmp)
	{
		free(*tmp);
		++tmp;
	}
	free(arr);
}
