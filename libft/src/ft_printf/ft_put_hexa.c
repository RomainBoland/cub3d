/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:59:53 by rboland           #+#    #+#             */
/*   Updated: 2024/10/28 10:59:53 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	print_hexa(unsigned int nbr, int upper_case)
{
	static char	upper_digits[] = "0123456789ABCDEF";
	static char	lower_digits[] = "0123456789abcdef";
	size_t		count;

	count = 0;
	if (nbr >= 16)
		count += print_hexa(nbr / 16, upper_case);
	if (upper_case)
		write(1, &upper_digits[nbr % 16], 1);
	else
		write(1, &lower_digits[nbr % 16], 1);
	return (count + 1);
}

int	ft_put_hexa(unsigned int nbr, int upper_case)
{
	if (nbr == 0)
	{
		return (write(1, "0", 1));
	}
	return (print_hexa(nbr, upper_case));
}
