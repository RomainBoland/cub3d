/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:41:18 by rboland           #+#    #+#             */
/*   Updated: 2024/10/21 13:49:15 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}
/*
static char	ft_toupperq(unsigned int i, char c)
{
	(void)i;

	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
#include <stdio.h>
int	main(void)
{
	char	*original = NULL;
	char	*result = ft_strmapi(original, ft_toupperq);

	if (result)
	{
		printf("Original : %s\n", original);
		printf("Result : %s\n", result);
		free(result);
	} else
	{
		printf("Erreur memoire");
	}
	return (0);
}
*/
