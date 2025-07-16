/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:34:33 by rboland           #+#    #+#             */
/*   Updated: 2024/10/21 14:45:35 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}
/*
void	ft_exmpl_toupper(unsigned int i, char *c)
{
	(void)i;

	if ((*c) >= 'a' && (*c) <= 'z')
		*c = *c - 32;
}
#include <stdio.h>
int	main(void)
{
	char	str[50] = "hello world!";

	printf("Str avant fct : %s\n", str);
	ft_striteri(str, ft_exmpl_toupper);
	printf("Str apres fct : %s\n", str);

	return (0);
}
*/
