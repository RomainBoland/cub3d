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

void	render_floor(t_config *config, t_f_l *f_l, t_data *img, int x)
{
	int	adjusted_y;

	adjusted_y = f_l->y - f_l->pitch_offset;
	if (adjusted_y >= WINDOW_HEIGHT / 2)
	{
		clc_wrld_pos(config, x, adjusted_y, f_l);
		f_l->tex_x = (int)(f_l->world_x * config->tex.floor.width);
		f_l->tex_y = (int)(f_l->world_y * config->tex.floor.height);
		f_l->color = get_txt_pxl(&config->tex.floor, f_l->tex_x, f_l->tex_y);
		f_l->dx = f_l->world_x - config->player.pos_x;
		f_l->dy = f_l->world_y - config->player.pos_y;
		f_l->distance = fast_distance_approximation(f_l->dx, f_l->dy);
		f_l->color = apply_distance_shading(f_l->color, f_l->distance);
		my_mlx_pixel_put(img, x, f_l->y, f_l->color);
	}
	else
		my_mlx_pixel_put(img, x, f_l->y, 0x202020);
}

void	render_ceilling(t_config *config, t_f_l *f_l, t_data *img, int x)
{
	int	adjusted_y;

	adjusted_y = f_l->y - f_l->pitch_offset;
	if (adjusted_y <= WINDOW_HEIGHT / 2)
	{
		clc_wrld_pos(config, x, adjusted_y, f_l);
		f_l->tex_x = (int)(f_l->world_x * config->tex.ceiling.width);
		f_l->tex_y = (int)(f_l->world_y * config->tex.ceiling.height);
		f_l->color = get_txt_pxl(&config->tex.ceiling, f_l->tex_x, f_l->tex_y);
		f_l->dx = f_l->world_x - config->player.pos_x;
		f_l->dy = f_l->world_y - config->player.pos_y;
		f_l->distance = fast_distance_approximation(f_l->dx, f_l->dy);
		f_l->color = apply_distance_shading(f_l->color, f_l->distance);
		my_mlx_pixel_put(img, x, f_l->y, f_l->color);
	}
	else
		my_mlx_pixel_put(img, x, f_l->y, 0x404040);
}

void	render_floor_ceiling_column(t_config *config, t_data *img, int x,
									t_wall_draw draw)
{
	t_f_l	f_l;

	f_l.sin_angle = sin(config->player.angle);
	f_l.cos_angle = cos(config->player.angle);
	f_l.pitch_offset = (int)(config->player.pitch * WINDOW_HEIGHT * 0.5f);
	f_l.y = 0;
	while (f_l.y < draw.wall_start)
	{
		render_ceilling(config, &f_l, img, x);
		f_l.y++;
	}
	f_l.y = draw.wall_end + 1;
	while (f_l.y < WINDOW_HEIGHT)
	{
		render_floor(config, &f_l, img, x);
		f_l.y++;
	}
}
