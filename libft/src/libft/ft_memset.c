/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:16:16 by rboland           #+#    #+#             */
/*   Updated: 2024/10/14 11:18:54 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)pointer;
	while (len > 0)
	{
		*(temp++) = (unsigned char) value;
		len--;
	}
	return (pointer);
}

/*
#include <stdio.h>
#include <string.h>

void	*ft_memset(void *pointer, int value, size_t len);

int	main(void)
{
	char str[50] = "Salut ca va ?";

	printf("Avant ft_memset: %s\n", str);

	ft_memset(str, 'A', 5);

	printf("Après ft_memset: %s\n", str);

	return (0);
}
*/
