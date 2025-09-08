/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceiling_floor_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:22:54 by nsaillez          #+#    #+#             */
/*   Updated: 2025/09/08 14:25:07 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
	get_safe_texture_pixel;
*/

unsigned	int	get_txt_pxl(t_texture *texture, int x, int y)
{
	x = x & (texture->width - 1);
	y = y & (texture->height - 1);
	return (get_texture_pixel(texture, x, y));
}

float	abs_val(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

float	fast_distance_approximation(float dx, float dy)
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

void	clc_wrld_pos(t_config *cfg, int s_x, int s_y, t_f_l *f_l)
{
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;
	float	row_distance;

	camera_x = 2.0f * s_x / (float) WINDOW_WIDTH - 1.0f;
	ray_dir_x = f_l->cos_angle + (-f_l->sin_angle * FOV_HALF_TAN) * camera_x;
	ray_dir_y = f_l->sin_angle + (f_l->cos_angle * FOV_HALF_TAN) * camera_x;
	if (s_y > WINDOW_HEIGHT / 2)
		row_distance = (0.5f * WINDOW_HEIGHT) / (s_y - WINDOW_HEIGHT / 2);
	else
		row_distance = (0.5f * WINDOW_HEIGHT) / (WINDOW_HEIGHT / 2 - s_y);
	f_l->world_x = cfg->player.pos_x + row_distance * ray_dir_x;
	f_l->world_y = cfg->player.pos_y + row_distance * ray_dir_y;
	f_l->distance = row_distance;
}
