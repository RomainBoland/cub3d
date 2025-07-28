/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:21:08 by rboland           #+#    #+#             */
/*   Updated: 2025/07/27 16:21:08 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned int	apply_distance_shading(unsigned int color, float distance)
{
	int		r;
	int		g;
	int		b;
	float	shade;

	if (distance <= 3.0)
		return (color);
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	shade = 1.0 - (distance - 3.0) / 7.5;
	if (shade < 0.1)
		shade = 0.1;
	if (shade > 1.0)
		shade = 1.0;
	r = (int)(r * shade);
	g = (int)(g * shade);
	b = (int)(b * shade);
	return ((r << 16) | (g << 8) | b);
}

void	draw_textured_column(t_column_params *params)
{
	t_texture_draw	tex_draw;
	int				y;
	int				tex_y;
	unsigned int	color;

	tex_draw.step = (float)params->texture->height / params->draw->wall_height;
	tex_draw.tex_pos = 0.0;
	if (params->draw->wall_start < 0)
		tex_draw.tex_pos = (-params->draw->wall_start) * tex_draw.step;
	y = params->draw->draw_start;
	while (y <= params->draw->draw_end)
	{
		tex_y = (int)tex_draw.tex_pos;
		if (tex_y >= params->texture->height)
			tex_y = params->texture->height - 1;
		if (tex_y < 0)
			tex_y = 0;
		color = get_texture_pixel(params->texture, params->draw->tex_x, tex_y);
		color = apply_distance_shading(color, params->distance);
		my_mlx_pixel_put(params->img, params->x, y, color);
		tex_draw.tex_pos += tex_draw.step;
		y++;
	}
}
