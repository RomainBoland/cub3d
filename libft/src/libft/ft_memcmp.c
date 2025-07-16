/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:36:29 by rboland           #+#    #+#             */
/*   Updated: 2024/10/20 09:36:33 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	size_t			i;

	tmp1 = (unsigned char *) s1;
	tmp2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)tmp1[i] != (unsigned char)tmp2[i])
			return ((unsigned char)tmp1[i] - (unsigned char)tmp2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int main(void)
{
	printf("%d\n", ft_memcmp("oui", "oui", 3));
	return (0);
}
*/
