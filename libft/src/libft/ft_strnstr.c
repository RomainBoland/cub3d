/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:49:40 by rboland           #+#    #+#             */
/*   Updated: 2024/10/20 10:50:41 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[i])
	{
		return ((char *)&haystack[i]);
	}
	while (haystack[i] && i < len)
	{
		j = 0;
		while ((haystack[i + j])
			&& (haystack[i + j] == needle[j] && i + j < len))
		{
			if (!needle[j + 1])
			{
				return ((char *)&haystack[i]);
			}
			j++;
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int     main(void)
{
        char    str[] = "Hello world";
        char    to_find[] = "lo";

        printf("%s\n", ft_strnstr(str, to_find, 12));
        return (0);
}
*/
