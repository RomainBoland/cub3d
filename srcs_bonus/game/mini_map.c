/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:46:37 by nsaillez          #+#    #+#             */
/*   Updated: 2025/08/21 12:16:56 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_angle_in_fov(float angle, float fov_start, float fov_end)
{
	angle = normalize_angle(angle);
	fov_start = normalize_angle(fov_start);
	fov_end = normalize_angle(fov_end);
	if (fov_start < fov_end)
		return (angle >= fov_start && angle <= fov_end);
	return (angle >= fov_start || angle <= fov_end);
}

static void	init_minimap_data(t_minimap_data *data, t_config *config)
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

static void	screen_to_world(t_minimap_data *data, int screen_x, int screen_y)
{
	float	pixel_x;
	float	pixel_y;

	pixel_x = screen_x - data->center_x;
	pixel_y = screen_y - data->center_y;
	data->world_x = data->player_x + (pixel_x / data->scale);
	data->world_y = data->player_y + (pixel_y / data->scale);
}

static unsigned int	get_door_color(t_interactive *interactive)
{
	if (interactive->door_state == DOOR_CLOSED_LOCKED)
		return (COLOR_DOOR_LOCKED);
	if (interactive->door_state == DOOR_CLOSED_UNLOCKED)
		return (COLOR_DOOR_UNLOCKED);
	if (interactive->door_state == DOOR_OPENED_UNLOCKED)
		return (COLOR_DOOR_OPEN);
	return (COLOR_WALL);
}

static unsigned int	get_lever_color(t_interactive *interactive)
{
	if (interactive->is_activated)
		return (COLOR_LEVER_ON);
	return (COLOR_LEVER_OFF);
}

static unsigned int	get_interactive_color(t_config *config,
	int map_x, int map_y)
{
	t_interactive	*interactive;
	char			cell;

	cell = config->map[map_y][map_x];
	interactive = find_interactive_at(config, map_x, map_y);
	if (!interactive)
		return (COLOR_WALL);
	if (cell == 'D')
		return (get_door_color(interactive));
	if (cell == 'L')
		return (get_lever_color(interactive));
	return (COLOR_WALL);
}

static unsigned int	get_map_cell_color(t_config *config, int map_x, int map_y)
{
	char	cell;

	if (map_y < 0 || map_y >= config->map_height)
		return (COLOR_BACKGROUND);
	if (map_x < 0 || map_x >= (int)ft_strlen(config->map[map_y]))
		return (COLOR_BACKGROUND);
	cell = config->map[map_y][map_x];
	if (cell == '1')
		return (COLOR_WALL);
	if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
		return (COLOR_EMPTY);
	if (cell == 'D' || cell == 'L')
		return (get_interactive_color(config, map_x, map_y));
	return (COLOR_BACKGROUND);
}

static unsigned int	blend_colors(unsigned int base_color,
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

static void	draw_minimap_pixel(t_game *game, int x, int y, unsigned int color)
{
	my_mlx_pixel_put(&game->img, x + MINIMAP_OFFSET_X,
		y + MINIMAP_OFFSET_Y, color);
}

static int	is_within_circle(int x, int y, t_minimap_data *data)
{
	int	dx;
	int	dy;

	dx = x - data->center_x;
	dy = y - data->center_y;
	return (dx * dx + dy * dy <= MINIMAP_RADIUS * MINIMAP_RADIUS);
}

static void	draw_map_geometry(t_game *game, t_minimap_data *data)
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

static unsigned int	get_current_pixel_color(t_game *game, int x, int y)
{
	char	*pixel_addr;

	pixel_addr = game->img.addr + ((y + MINIMAP_OFFSET_Y)
			* game->img.line_length + (x + MINIMAP_OFFSET_X)
			* (game->img.bits_per_pixel / 8));
	return (*(unsigned int *)pixel_addr);
}

static int	should_draw_fov_pixel(int x, int y, t_minimap_data *data)
{
	float	distance_sq;

	distance_sq = (x - data->center_x) * (x - data->center_x)
		+ (y - data->center_y) * (y - data->center_y);
	return (distance_sq <= MINIMAP_RADIUS * MINIMAP_RADIUS && distance_sq > 0);
}

static void	draw_fov_pixel_if_needed(t_game *game, int x, int y,
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

static void	draw_fov_overlay(t_game *game, t_minimap_data *data)
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

static int	is_border_pixel(int x, int y, t_minimap_data *data)
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

static void	draw_minimap_border(t_game *game, t_minimap_data *data)
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

static int	is_player_pixel(int x, int y, t_minimap_data *data)
{
	float	distance_sq;
	int		player_radius;

	player_radius = 5;
	distance_sq = (x - data->center_x) * (x - data->center_x)
		+ (y - data->center_y) * (y - data->center_y);
	return (distance_sq <= player_radius * player_radius);
}

static void	draw_player(t_game *game, t_minimap_data *data)
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

void	update_mini_map(t_game *game)
{
	t_minimap_data	data;

	init_minimap_data(&data, game->config);
	draw_map_geometry(game, &data);
	draw_fov_overlay(game, &data);
	draw_minimap_border(game, &data);
	draw_player(game, &data);
}
