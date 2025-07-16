/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:23:49 by rboland           #+#    #+#             */
/*   Updated: 2024/10/20 09:24:27 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*tmp;

	tmp = (char *)s;
	while (n > 0)
	{
		*(tmp++) = 0;
		n--;
	}
}
/*
#include <stdio.h>

int	main(void)
{
	char str[50] = "Hello World!";

	printf("Str avant bzero : %s\n", str);
	ft_bzero(str + 5, 5);
	printf("Str apres bzero : %s\n", str);
	return (0);
}
*/
