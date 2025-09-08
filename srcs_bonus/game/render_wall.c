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

#include "cub3d_bonus.h"

t_texture	*get_cell_texture(t_config *config, int map_x,
							int map_y, int wall_dir)
{
	char			cell;
	t_interactive	*interactive;

	if (map_y < 0 || map_y >= config->map_height
		|| map_x < 0 || map_x >= (int)ft_strlen(config->map[map_y]))
		return (get_wall_texture(config, wall_dir));
	cell = config->map[map_y][map_x];
	if (cell == 'D')
	{
		interactive = find_interactive_at(config, map_x, map_y);
		if (interactive)
			return (get_door_texture(config, interactive));
	}
	else if (cell == 'L')
	{
		interactive = find_interactive_at(config, map_x, map_y);
		if (interactive)
			return (get_lever_texture(config, interactive, wall_dir));
	}
	return (get_wall_texture(config, wall_dir));
}

static t_wall_draw	calculate_wall_bounds(t_ray ray, t_config *config)
{
	int				pitch_offset;
	t_wall_draw		draw;

	draw.wall_height = (int)(WINDOW_HEIGHT / ray.distance);
	if (draw.wall_height > WINDOW_HEIGHT * 3)
		draw.wall_height = WINDOW_HEIGHT * 3;
	if (draw.wall_height < 1)
		draw.wall_height = 1;
	pitch_offset = (int)(config->player.pitch * WINDOW_HEIGHT * 0.5f);
	draw.wall_start = (WINDOW_HEIGHT - draw.wall_height) / 2 + pitch_offset;
	draw.wall_end = draw.wall_start + draw.wall_height;
	return (draw);
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
	t_texture		*texture;
	t_column_params	params;
	t_wall_draw		draw;

	draw = calculate_wall_bounds(ray, config);
	calculate_draw_bounds(draw.wall_start, draw.wall_end,
		&draw.draw_start, &draw.draw_end);
	texture = get_cell_texture(config, ray.map_x, ray.map_y, ray.wall_dir);
	draw.tex_x = get_texture_x(texture, ray.wall_x);
	render_floor_ceiling_column(config, img, x, draw.draw_start, draw.draw_end);
	params.img = img;
	params.x = x;
	params.draw = &draw;
	params.texture = texture;
	params.distance = ray.distance;
	draw_textured_column(&params);
}
