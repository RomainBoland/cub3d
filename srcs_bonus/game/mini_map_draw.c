/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:30:36 by nsaillez          #+#    #+#             */
/*   Updated: 2025/09/08 10:20:46 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_map_geometry(t_game *game, t_minimap_data *data)
{
	int				x;
	int				y;
	unsigned int	map_color;

	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			if (is_within_circle(x, y, data))
			{
				screen_to_world(data, x, y);
				map_color = get_map_cell_color(game->config,
						(int)data->world_x, (int)data->world_y);
				draw_minimap_pixel(game, x, y, map_color);
			}
			x++;
		}
		y++;
	}
}

void	draw_fov_pixel_if_needed(t_game *game, int x, int y,
				t_minimap_data *data)
{
	float			angle_to_pixel;
	unsigned int	current_color;

	angle_to_pixel = atan2(y - data->center_y, x - data->center_x);
	if (is_angle_in_fov(angle_to_pixel, data->fov_start, data->fov_end))
	{
		current_color = get_current_pixel_color(game, x, y);
		draw_minimap_pixel(game, x, y,
			blend_colors(current_color, COLOR_FOV));
	}
}

void	draw_fov_overlay(t_game *game, t_minimap_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			if (should_draw_fov_pixel(x, y, data))
				draw_fov_pixel_if_needed(game, x, y, data);
			x++;
		}
		y++;
	}
}

void	draw_minimap_border(t_game *game, t_minimap_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			if (is_border_pixel(x, y, data))
				draw_minimap_pixel(game, x, y, COLOR_BORDER);
			x++;
		}
		y++;
	}
}
void	draw_player(t_game *game, t_minimap_data *data)
{
	int	x;
	int	y;
	int	player_radius;

	player_radius = 5;
	y = data->center_y - player_radius;
	while (y <= data->center_y + player_radius)
	{
		x = data->center_x - player_radius;
		while (x <= data->center_x + player_radius)
		{
			if (x >= 0 && x < MINIMAP_SIZE && y >= 0 && y < MINIMAP_SIZE)
			{
				if (is_player_pixel(x, y, data))
					draw_minimap_pixel(game, x, y, COLOR_PLAYER);
			}
			x++;
		}
		y++;
	}
}
