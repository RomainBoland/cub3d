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

#include "cub3d_bonus.h"

static int	check_neighbor_up(t_config *config, int x, int y)
{
	int	nx;
	int	ny;

	nx = x;
	ny = y - 1;
	if (!is_position_valid(config, nx, ny))
		return (0);
	if (ft_isspace(config->map[ny][nx]))
		return (0);
	return (1);
}

static int	check_neighbor_down(t_config *config, int x, int y)
{
	int	nx;
	int	ny;

	nx = x;
	ny = y + 1;
	if (!is_position_valid(config, nx, ny))
		return (0);
	if (ft_isspace(config->map[ny][nx]))
		return (0);
	return (1);
}

static int	check_neighbor_sides(t_config *config, int x, int y)
{
	int	nx;
	int	ny;

	nx = x + 1;
	ny = y;
	if (!is_position_valid(config, nx, ny))
		return (0);
	if (ft_isspace(config->map[ny][nx]))
		return (0);
	nx = x - 1;
	ny = y;
	if (!is_position_valid(config, nx, ny))
		return (0);
	if (ft_isspace(config->map[ny][nx]))
		return (0);
	return (1);
}

static int	check_cell_neighbors(t_config *config, int x, int y)
{
	if (!check_neighbor_up(config, x, y))
		return (0);
	if (!check_neighbor_down(config, x, y))
		return (0);
	if (!check_neighbor_sides(config, x, y))
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
			if (config->map[y][x] == '0' || config->map[y][x] == 'N'
				|| config->map[y][x] == 'S' || config->map[y][x] == 'E'
				|| config->map[y][x] == 'W')
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
