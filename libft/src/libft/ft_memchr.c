/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:36:07 by rboland           #+#    #+#             */
/*   Updated: 2024/10/20 09:36:09 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	tmp_c;
	unsigned char	*tmp_s;
	size_t			i;

	i = 0;
	tmp_c = (unsigned char) c;
	tmp_s = (unsigned char *) s;
	while (i < n)
	{
		if (tmp_s[i] == tmp_c)
			return ((void *)&tmp_s[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int main(void)
{
	printf("%p\n", ft_memchr("oui", 'u', 2));
	return (0);
}
*/
