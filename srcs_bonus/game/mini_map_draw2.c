/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_draw2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:32:40 by nsaillez          #+#    #+#             */
/*   Updated: 2025/09/08 10:20:57 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_minimap_data(t_minimap_data *data, t_config *config)
{
	float	reduced_fov;

	data->player_x = config->player.pos_x;
	data->player_y = config->player.pos_y;
	data->player_angle = config->player.angle;
	data->center_x = MINIMAP_RADIUS;
	data->center_y = MINIMAP_RADIUS;
	data->scale = (float)MINIMAP_RADIUS / MINIMAP_TILES_RADIUS;
	reduced_fov = FOV_HALF_TAN * 0.7f;
	data->fov_start = normalize_angle(data->player_angle - reduced_fov);
	data->fov_end = normalize_angle(data->player_angle + reduced_fov);
}

void	screen_to_world(t_minimap_data *data, int screen_x, int screen_y)
{
	float	pixel_x;
	float	pixel_y;

	pixel_x = screen_x - data->center_x;
	pixel_y = screen_y - data->center_y;
	data->world_x = data->player_x + (pixel_x / data->scale);
	data->world_y = data->player_y + (pixel_y / data->scale);
}

unsigned int	blend_colors(unsigned int base_color,
					unsigned int overlay_color)
{
	unsigned int	r_result;
	unsigned int	g_result;
	unsigned int	b_result;

	r_result = ((base_color >> 16) & 0xFF) + ((overlay_color >> 16) & 0xFF);
	g_result = ((base_color >> 8) & 0xFF) + ((overlay_color >> 8) & 0xFF);
	b_result = (base_color & 0xFF) + (overlay_color & 0xFF);
	return (((r_result / 2) << 16) | ((g_result / 2) << 8) | (b_result / 2));
}

void	draw_minimap_pixel(t_game *game, int x, int y, unsigned int color)
{
	my_mlx_pixel_put(&game->img, x + MINIMAP_OFFSET_X,
		y + MINIMAP_OFFSET_Y, color);
}

int	should_draw_fov_pixel(int x, int y, t_minimap_data *data)
{
	float	distance_sq;

	distance_sq = (x - data->center_x) * (x - data->center_x)
		+ (y - data->center_y) * (y - data->center_y);
	return (distance_sq <= MINIMAP_RADIUS * MINIMAP_RADIUS && distance_sq > 0);
}
