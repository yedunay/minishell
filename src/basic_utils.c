/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:07:54 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:17:32 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Returns the size of the given NULL-terminated array 'arr'.
size_t	arr_size(const void **arr)
{
	size_t	size;

	size = 0;
	while (arr && arr[size])
		++size;
	return (size);
}

// Allocates 'size' bytes of memory and returns a pointer to it.
// Exits properly if memory allocation fails.
void	*p_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		restore_exit(EXIT_FAILURE);
	return (ptr);
}

// Restores the default print signal config and exits returning 'exit_status'.
void	restore_exit(int exit_status)
{
	signals_print_handler(TRUE);
	exit(exit_status);
}

// Copies and concatenates the string 'src' into 'dst', taking the full size of
// 'dst' (defined by 'dstsize') and ensuring NULL-termination.
// Returns the total length of the string it tried to create.
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*dst_cpy;
	char	*src_cpy;
	size_t	dlen;
	size_t	n;

	n = dstsize;
	dst_cpy = dst;
	src_cpy = (char *)src;
	while (n-- != 0 && *dst)
		++dst;
	dlen = dst - dst_cpy;
	n = dstsize - dlen;
	if (n == 0)
		return (dlen + ft_strlen(src));
	while (*src)
	{
		if (n != 1)
		{
			*dst++ = *src;
			--n;
		}
		++src;
	}
	*dst = '\0';
	return (dlen + (src - src_cpy));
}
