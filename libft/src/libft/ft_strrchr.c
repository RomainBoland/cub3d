/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:50:56 by rboland           #+#    #+#             */
/*   Updated: 2024/10/20 10:50:58 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last;
	char	tmp_c;

	tmp_c = (char)c;
	i = 0;
	last = NULL;
	while (s[i])
	{
		if (s[i] == tmp_c)
			last = (char *)&s[i];
		i++;
	}
	if (tmp_c == '\0')
		last = (char *)&s[i];
	return (last);
}
/*
#include <stdio.h>

int	main(void)
{
	char *ptr = ft_strrchr("Hello World!", 'W');
	printf("%s\n", ptr);
	return (0);
}
*/
