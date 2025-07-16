/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:07:29 by rboland           #+#    #+#             */
/*   Updated: 2024/10/14 11:13:34 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;

	if (!dst && !src)
		return (dst);
	temp_dst = (unsigned char *) dst;
	temp_src = (unsigned char *) src;
	while (size > 0)
	{
		*(temp_dst++) = *(temp_src++);
		size--;
	}
	return (dst);
}
/*
#include <stdio.h>
int	main(void)
{
	char src[50] = "Hello, World!";
	char dst[50];

	printf("Avant ft_memcpy:\n");
	printf("Source: %s\n", src);
	printf("Destination: %s\n", dst);
	ft_memcpy(dst, src, 13);
	printf("\nApres ft_memcpy:\n");
	printf("Source: %s\n", src);
	printf("Destination: %s\n", dst);
	return (0);
}
*/
