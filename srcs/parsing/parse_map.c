/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 12:56:44 by rboland           #+#    #+#             */
/*   Updated: 2025/07/19 12:56:44 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int find_player(t_config *config)
{
	int	x;
	int	y;
	int player_count;

	player_count = 0;
	y = 0;
	while (y < config->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(config->map[y]))
		{
			if (config->map[y][x] == 'N' || config->map[y][x] == 'S' ||
				config->map[y][x] == 'E' || config->map[y][x] == 'W')
			{
				if (player_count > 0)
					return (0);
				config->player.x = x;
				config->player.y = y;
				config->player.direction = config->map[y][x];
				// set_player_angle(config);
				player_count++;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map_characters(t_config *config)
{
	int	x;
	int	y;

	y = 0;
	while (y < config->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(config->map[y]))
		{
			if (!is_valid_char(config->map[y][x]))
			{
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_config *config)
{
	if (!validate_map_characters(config))
		return (print_error("Invalid characters in map"), 0);	
	if (!find_player(config))
		return (print_error("Map must have exactly one player"), 0);
	if (!check_walls_around_spaces(config))
		return (print_error("Walkable areas cant be surrounded by holes"), 0);
	return (1);
}
