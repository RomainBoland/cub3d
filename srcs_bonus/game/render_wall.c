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

t_texture *get_cell_texture(t_config *config, int map_x, int map_y, int wall_dir)
{
    char cell;
    t_interactive *interactive;
    
    // Bounds check
    if (map_y < 0 || map_y >= config->map_height ||
        map_x < 0 || map_x >= (int)ft_strlen(config->map[map_y]))
        return get_wall_texture(config, wall_dir);
    
    cell = config->map[map_y][map_x];
    
    // Handle interactive elements
    if (cell == 'D') // Door
    {
        interactive = find_interactive_at(config, map_x, map_y);
        if (interactive)
            return get_door_texture(config, interactive);
    }
    else if (cell == 'L') // Lever
    {
        interactive = find_interactive_at(config, map_x, map_y);
        if (interactive)
            return get_lever_texture(config, interactive, wall_dir); // Use wall_dir instead of player_angle
    }
    
    // Regular wall textures
    return get_wall_texture(config, wall_dir);
}

static void	calculate_wall_bounds(t_ray ray, t_config *config,
							int *wall_height, int *wall_start, int *wall_end)
{
	int	pitch_offset;

	*wall_height = (int)(WINDOW_HEIGHT / ray.distance);
	if (*wall_height > WINDOW_HEIGHT * 3)
		*wall_height = WINDOW_HEIGHT * 3;
	if (*wall_height < 1)
		*wall_height = 1;
	pitch_offset = (int)(config->player.pitch * WINDOW_HEIGHT * 0.5f);
	*wall_start = (WINDOW_HEIGHT - *wall_height) / 2 + pitch_offset;
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
	t_column_params	params;

	calculate_wall_bounds(ray, config, &draw.wall_height,
		&draw.wall_start, &draw.wall_end);
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
