/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:06:04 by rboland           #+#    #+#             */
/*   Updated: 2025/07/19 15:06:04 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || ft_isspace((unsigned char)c));
}

int	is_position_valid(t_config *config, int x, int y)
{
	if (x < 0 || y < 0 || y >= config->map_height)
		return (0);
	if (x >= (int)ft_strlen(config->map[y]))
		return (0);
	return (1);
}
