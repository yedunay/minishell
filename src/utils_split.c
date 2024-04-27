/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:09 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:16:51 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	count_substr(char *s, char c)
{
	size_t	count;
	int		flag;

	flag = 0;
	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (flag == 0)
			{
				flag = 1;
				count++;
			}
		}
		else
			flag = 0;
		s++;
	}
	return (count);
}

static char	*pop_str(char **s, char c)
{
	char	*substr;
	char	*str;
	size_t	strlen;

	str = *s;
	strlen = 0;
	while (*str && *str == c)
		str++;
	while (str[strlen] && str[strlen] != c)
		strlen++;
	substr = (char *)p_malloc((strlen + 1) * sizeof(char));
	ft_strlcpy(substr, str, strlen + 1);
	*s = str + strlen;
	return (substr);
}

static void	*freearr(char **arr)
{
	char	**arrcpy;

	arrcpy = arr;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(arrcpy);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	substr_count;
	char	*str;
	size_t	count;

	if (!s)
		return (NULL);
	count = 0;
	str = (char *)s;
	substr_count = count_substr(str, c);
	arr = (char **)p_malloc((substr_count + 1) * sizeof(char *));
	while (count < substr_count)
	{
		arr[count] = pop_str(&str, c);
		if (arr[count++] == NULL)
			return (freearr(arr));
	}
	arr[count] = NULL;
	return (arr);
}
