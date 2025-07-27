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

#include "cub3d.h"

void	draw_ceiling_and_floor(t_data *img, int x, t_wall_draw *draw,
	t_colors *colors)
{
	int	y;

	y = 0;
	while (y < draw->draw_start)
	{
		my_mlx_pixel_put(img, x, y, colors->c_color);
		y++;
	}
	y = draw->draw_end + 1;
	while (y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(img, x, y, colors->f_color);
		y++;
	}
}

void	draw_textured_column(t_data *img, int x, t_wall_draw *draw,
	t_texture *texture, float distance)
{
	t_texture_draw	tex_draw;
	int				y;
	int				tex_y;
	unsigned int	color;

	tex_draw.step = (float)texture->height / draw->wall_height;
	tex_draw.tex_pos = 0.0;
	if (draw->wall_start < 0)
		tex_draw.tex_pos = (-draw->wall_start) * tex_draw.step;
	y = draw->draw_start;
	while (y <= draw->draw_end)
	{
		tex_y = (int)tex_draw.tex_pos;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		if (tex_y < 0)
			tex_y = 0;
		color = get_texture_pixel(texture, draw->tex_x, tex_y);
		color = apply_distance_shading(color, distance);
		my_mlx_pixel_put(img, x, y, color);
		tex_draw.tex_pos += tex_draw.step;
		y++;
	}
}
