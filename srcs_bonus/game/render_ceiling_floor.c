/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceiling_floor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:52:54 by rboland           #+#    #+#             */
/*   Updated: 2025/07/28 12:52:54 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static unsigned	int	get_safe_texture_pixel(t_texture *texture, int x, int y)
{
	x = x & (texture->width - 1);
	y = y & (texture->height - 1);
	return (get_texture_pixel(texture, x, y));
}

static float	abs_val(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

static float	fast_distance_approximation(float dx, float dy)
{
	float	abs_dx;
	float	abs_dy;

	abs_dx = abs_val(dx);
	abs_dy = abs_val(dy);
	if (abs_dx > abs_dy)
		return (abs_dx + 0.5f * abs_dy);
	else
		return (abs_dy + 0.5f * abs_dx);
}

// Optimized world position calculation (no static variables)
static void	calculate_world_position(t_config *config, int screen_x, int screen_y, float cos_angle, float sin_angle, float *world_x, float *world_y, float *distance)
{
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;
	float	row_distance;

	camera_x= 2.0f * screen_x / (float)WINDOW_WIDTH - 1.0f;
	ray_dir_x = cos_angle + (-sin_angle * FOV_HALF_TAN) * camera_x;
	ray_dir_y = sin_angle + (cos_angle * FOV_HALF_TAN) * camera_x;
	if (screen_y > WINDOW_HEIGHT / 2)
		row_distance = (0.5f * WINDOW_HEIGHT) / (screen_y - WINDOW_HEIGHT / 2);
	else
		row_distance = (0.5f * WINDOW_HEIGHT) / (WINDOW_HEIGHT / 2 - screen_y);
	*world_x = config->player.pos_x + row_distance * ray_dir_x;
	*world_y = config->player.pos_y + row_distance * ray_dir_y;
	*distance = row_distance;
}

void	render_floor_ceiling_column(t_config *config, t_data *img, int x, 
								  int wall_start, int wall_end)
{
	int				y;
	float			world_x;
	float			world_y;
	float			distance;
	int				tex_x;
	int				tex_y;
	unsigned int	color;
	float			dx;
	float			dy;
	float			cos_angle;
	float			sin_angle;
	int				pitch_offset;

	sin_angle = sin(config->player.angle);
	cos_angle = cos(config->player.angle);
	pitch_offset = (int)(config->player.pitch * WINDOW_HEIGHT * 0.5f);
	y = 0;
	while (y < wall_start)
	{
		int adjusted_y = y - pitch_offset;
		if (adjusted_y <= WINDOW_HEIGHT / 2) {
			calculate_world_position(config, x, adjusted_y, cos_angle, sin_angle, &world_x, &world_y, &distance);
			tex_x = (int)(world_x * config->tex.ceiling.width);
			tex_y = (int)(world_y * config->tex.ceiling.height);
			color = get_safe_texture_pixel(&config->tex.ceiling, tex_x, tex_y);
			dx = world_x - config->player.pos_x;
			dy = world_y - config->player.pos_y;
			distance = fast_distance_approximation(dx, dy);
			color = apply_distance_shading(color, distance);
			my_mlx_pixel_put(img, x, y, color);
		} else
			my_mlx_pixel_put(img, x, y, 0x404040);
		y++;
	}
	y = wall_end + 1;
	while (y < WINDOW_HEIGHT)
	{
		int adjusted_y = y - pitch_offset;        
		if (adjusted_y >= WINDOW_HEIGHT / 2)
		{
			calculate_world_position(config, x, adjusted_y, cos_angle, sin_angle, &world_x, &world_y, &distance);
			tex_x = (int)(world_x * config->tex.floor.width);
			tex_y = (int)(world_y * config->tex.floor.height);
			color = get_safe_texture_pixel(&config->tex.floor, tex_x, tex_y);
			dx = world_x - config->player.pos_x;
			dy = world_y - config->player.pos_y;
			distance = fast_distance_approximation(dx, dy);
			color = apply_distance_shading(color, distance);
			my_mlx_pixel_put(img, x, y, color);
		}
		else
			my_mlx_pixel_put(img, x, y, 0x202020);
		y++;
	}
}
