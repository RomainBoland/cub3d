/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:00:58 by rboland           #+#    #+#             */
/*   Updated: 2024/10/28 11:00:58 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	digits_count(int nbr)
{
	size_t	count;

	count = 0;
	if (nbr <= 0)
		count++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

static void	print_int(int nbr)
{
	static char	digits[] = "0123456789";

	if (nbr > 9)
		print_int(nbr / 10);
	write(1, &digits[nbr % 10], 1);
}

int	ft_put_int(int nbr)
{
	int	len;

	if (nbr == INT_MIN)
		return (write(1, "-2147483648", 11));
	len = digits_count(nbr);
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr *= -1;
	}
	print_int(nbr);
	return (len);
}
