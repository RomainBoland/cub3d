/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <romain.boland@hotmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:02:32 by rboland           #+#    #+#             */
/*   Updated: 2025/01/10 13:32:10 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	digits_count(unsigned long long nbr)
{
	size_t	count;

	count = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		count++;
		nbr = nbr / 16;
	}
	return (count);
}

static void	print_ptr(unsigned long long nbr)
{
	static char	digits[] = "0123456789abcdef";

	if (nbr >= 16)
		print_ptr(nbr / 16);
	write(1, &digits[nbr % 16], 1);
}

int	ft_put_ptr(void *ptr)
{
	if (ptr == NULL)
		return (write(1, "0x0", 3));
	write(1, "0x", 2);
	print_ptr((unsigned long long)ptr);
	return (digits_count((unsigned long long)ptr) + 2);
}
