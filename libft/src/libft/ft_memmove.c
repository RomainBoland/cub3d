/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:14:33 by rboland           #+#    #+#             */
/*   Updated: 2024/10/14 11:15:15 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;
	size_t			i;

	if (!dst && !src)
		return (dst);
	i = 0;
	temp_dst = (unsigned char *) dst;
	temp_src = (unsigned char *) src;
	if (temp_dst > temp_src)
	{
		while (len-- > 0)
			temp_dst[len] = temp_src[len];
	}
	else
	{
		while (i < len)
		{
			temp_dst[i] = temp_src[i];
			i++;
		}
	}
	return (dst);
}
/*
#include <stdio.h>
int	main(void)
{
	char test[50] = "Hello World!";
	char test2[50];

	printf("Dest avant : %s\n", test2);

	ft_memmove(test2, test, 13);

	printf("Dest apres : %s\n", test2);
	return (0);
}
*/
