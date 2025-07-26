/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:08:45 by rboland           #+#    #+#             */
/*   Updated: 2025/07/17 17:08:45 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	get_line_width(const char *line)
{
	size_t	len;

	len = ft_strlen(line);
	while (len > 0 && ft_isspace((unsigned char)line[len - 1]))
		len--;
	return (len);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r');
}

int	is_valid_tab_format(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
		i++;
	if (i != 2)
		return (0);
	return (1);
}
