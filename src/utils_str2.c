/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduvan <fduvan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:21:43 by ydunay            #+#    #+#             */
/*   Updated: 2024/02/17 18:59:14 by fduvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

// Outputs the string ’s’ to the given file descriptor.
void	ft_putstr_fd(const char *s, int fd)
{
	size_t	slen;

	if (!s)
		return ;
	slen = ft_strlen(s);
	write(fd, s, slen);
}

// Outputs the string ’s’ to the given file descriptor followed by a newline.
void	ft_putendl_fd(const char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
