/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:46:08 by rboland           #+#    #+#             */
/*   Updated: 2024/10/20 11:55:36 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_size;
	size_t	src_size;

	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (dst_size >= dstsize)
		dst_size = dstsize;
	if (dst_size == dstsize)
		return (dstsize + src_size);
	if (src_size < dstsize - dst_size)
		ft_memcpy(dst + dst_size, src, src_size + 1);
	else
	{
		ft_memcpy(dst + dst_size, src, dstsize - dst_size - 1);
		dst[dstsize - 1] = '\0';
	}
	return (dst_size + src_size);
}
/*
#include <stdio.h>
int	main(void)
{
	char str[50] = "Hello World!";
	printf("%lld\n", ft_strlcat(str, " Comment ca va ?", 23));
	printf("%s\n", str);
	return (0);
}
*/
