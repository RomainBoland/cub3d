/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:58:31 by rboland           #+#    #+#             */
/*   Updated: 2025/07/27 15:58:31 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_wall_bounds(t_ray ray, int *wall_height,
	int *wall_start, int *wall_end)
{
	*wall_height = (int)(WINDOW_HEIGHT / ray.distance);
	if (*wall_height > WINDOW_HEIGHT * 3)
		*wall_height = WINDOW_HEIGHT * 3;
	if (*wall_height < 1)
		*wall_height = 1;
	*wall_start = (WINDOW_HEIGHT - *wall_height) / 2;
	*wall_end = *wall_start + *wall_height;
}

static void	calculate_draw_bounds(int wall_start, int wall_end,
	int *draw_start, int *draw_end)
{
	if (wall_start < 0)
		*draw_start = 0;
	else
		*draw_start = wall_start;
	if (wall_end >= WINDOW_HEIGHT)
		*draw_end = WINDOW_HEIGHT - 1;
	else
		*draw_end = wall_end;
}

static int	get_texture_x(t_texture *texture, float wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * texture->width);
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	if (tex_x < 0)
		tex_x = 0;
	return (tex_x);
}

void	render_textured_wall(t_config *config, t_data *img, int x, t_ray ray)
{
	t_wall_draw		draw;
	t_texture		*texture;
	t_colors		colors;
	t_column_params	params;

	colors.f_color = (config->floor_color[0] << 16)
		| (config->floor_color[1] << 8) | config->floor_color[2];
	colors.c_color = (config->ceiling_color[0] << 16)
		| (config->ceiling_color[1] << 8) | config->ceiling_color[2];
	calculate_wall_bounds(ray, &draw.wall_height,
		&draw.wall_start, &draw.wall_end);
	calculate_draw_bounds(draw.wall_start, draw.wall_end,
		&draw.draw_start, &draw.draw_end);
	texture = get_wall_texture(config, ray.wall_dir);
	draw.tex_x = get_texture_x(texture, ray.wall_x);
	draw_ceiling_and_floor(img, x, &draw, &colors);
	params.img = img;
	params.x = x;
	params.draw = &draw;
	params.texture = texture;
	params.distance = ray.distance;
	draw_textured_column(&params);
}
