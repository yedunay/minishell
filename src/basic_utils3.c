/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:49:12 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 11:17:57 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Return the amount of digits needed to represent n in decimal (including
// sign, if needed).
static int	digit_count(int n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		digits++;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

// Allocates (with malloc(3)) and returns a string representing the integer
// received as an argument. Negative numbers must be handled.
// Exits properly if malloc fails.
char	*ft_itoa(int n)
{
	char	*str;
	int		strlen;

	strlen = digit_count(n);
	str = (char *)p_malloc((strlen + 1) * sizeof(char));
	str[strlen--] = '\0';
	if (n == 0)
		*str = '0';
	if (n < 0)
	{
		*str = '-';
		str[strlen--] = -(n % 10) + '0';
		n /= -10;
	}
	while (n != 0)
	{
		str[strlen--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dstcpy;
	unsigned char	*srccpy;

	if (dst == NULL && src == NULL)
		return (dst);
	dstcpy = (unsigned char *)dst;
	srccpy = (unsigned char *)src;
	while (n-- > 0)
		*dstcpy++ = *srccpy++;
	return (dst);
}
