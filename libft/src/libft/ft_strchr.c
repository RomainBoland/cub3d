/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:40:49 by rboland           #+#    #+#             */
/*   Updated: 2024/10/20 10:50:51 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	tmp_c;

	tmp_c = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == tmp_c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == tmp_c)
		return ((char *)&s[i]);
	return (NULL);
}
