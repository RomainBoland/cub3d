/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:46:37 by nsaillez          #+#    #+#             */
/*   Updated: 2025/09/08 10:21:19 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_angle_in_fov(float angle, float fov_start, float fov_end)
{
	angle = normalize_angle(angle);
	fov_start = normalize_angle(fov_start);
	fov_end = normalize_angle(fov_end);
	if (fov_start < fov_end)
		return (angle >= fov_start && angle <= fov_end);
	return (angle >= fov_start || angle <= fov_end);
}

int	is_within_circle(int x, int y, t_minimap_data *data)
{
	int	dx;
	int	dy;

	dx = x - data->center_x;
	dy = y - data->center_y;
	return (dx * dx + dy * dy <= MINIMAP_RADIUS * MINIMAP_RADIUS);
}

int	is_border_pixel(int x, int y, t_minimap_data *data)
{
	float	distance_sq;
	float	inner_radius_sq;
	float	outer_radius_sq;

	distance_sq = (x - data->center_x) * (x - data->center_x)
		+ (y - data->center_y) * (y - data->center_y);
	inner_radius_sq = (MINIMAP_RADIUS - 4) * (MINIMAP_RADIUS - 4);
	outer_radius_sq = MINIMAP_RADIUS * MINIMAP_RADIUS;
	return (distance_sq <= outer_radius_sq && distance_sq >= inner_radius_sq);
}

int	is_player_pixel(int x, int y, t_minimap_data *data)
{
	float	distance_sq;
	int		player_radius;

	player_radius = 5;
	distance_sq = (x - data->center_x) * (x - data->center_x)
		+ (y - data->center_y) * (y - data->center_y);
	return (distance_sq <= player_radius * player_radius);
}

void	update_mini_map(t_game *game)
{
	t_minimap_data	data;

	init_minimap_data(&data, game->config);
	draw_map_geometry(game, &data);
	draw_fov_overlay(game, &data);
	draw_minimap_border(game, &data);
	draw_player(game, &data);
}
