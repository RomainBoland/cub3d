/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:17:56 by rboland           #+#    #+#             */
/*   Updated: 2025/07/19 15:17:56 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_neighbor(t_config *config, int x, int y, int dx, int dy)
{
	int	nx;
	int	ny;

	nx = x + dx;
	ny = y + dy;
	if (!is_position_valid(config, nx, ny))
		return (0);
	if (ft_isspace(config->map[ny][nx]))
		return (0);
	return (1);
}

static int	check_cell_neighbors(t_config *config, int x, int y)
{
	if (!check_neighbor(config, x, y, 0, 1))
		return (0);
	if (!check_neighbor(config, x, y, 0, -1))
		return (0);
	if (!check_neighbor(config, x, y, 1, 0))
		return (0);
	if (!check_neighbor(config, x, y, -1, 0))
		return (0);
	return (1);
}

int	check_walls_around_spaces(t_config *config)
{
	int	x;
	int	y;

	y = 0;
	while (y < config->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(config->map[y]))
		{
			printf("%c", config->map[y][x]);
			if (is_walkable(config->map[y][x]))
			{
				if (!check_cell_neighbors(config, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
