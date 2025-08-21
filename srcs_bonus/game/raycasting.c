/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:24:46 by rboland           #+#    #+#             */
/*   Updated: 2025/07/19 17:24:46 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include "cub3d_bonus.h"

static t_texture	*get_lever_texture_side(t_config *config,
						t_interactive *lever, int texture_side)
{
	if (lever->is_activated)
	{
		if (texture_side == 0 && config->tex.lever_on_north.img)
			return (&config->tex.lever_on_north);
		else if (texture_side == 1 && config->tex.lever_on_south.img)
			return (&config->tex.lever_on_south);
		else if (config->tex.lever_on_base.img)
			return (&config->tex.lever_on_base);
		return (&config->tex.south);
	}
	else
	{
		if (texture_side == 0 && config->tex.lever_off_north.img)
			return (&config->tex.lever_off_north);
		else if (texture_side == 1 && config->tex.lever_off_south.img)
			return (&config->tex.lever_off_south);
		else if (config->tex.lever_off_base.img)
			return (&config->tex.lever_off_base);
		return (&config->tex.west);
	}
}

t_texture	*get_lever_texture(t_config *config, t_interactive *lever,
				int wall_dir)
{
	int	texture_side;

	if (!lever || lever->type != INTERACTIVE_LEVER)
		return (&config->tex.north);
	if (wall_dir == 0)
		texture_side = 0;
	else if (wall_dir == 1)
		texture_side = 1;
	else
		texture_side = 2;
	return (get_lever_texture_side(config, lever, texture_side));
}

t_texture	*get_door_texture(t_config *config, t_interactive *door)
{
	if (!door || door->type != INTERACTIVE_DOOR)
		return (&config->tex.north);
	if (door->door_state == DOOR_CLOSED_LOCKED)
	{
		if (config->tex.door_locked.img)
			return (&config->tex.door_locked);
		return (&config->tex.north);
	}
	else if (door->door_state == DOOR_CLOSED_UNLOCKED)
	{
		if (config->tex.door_unlocked.img)
			return (&config->tex.door_unlocked);
		return (&config->tex.south);
	}
	else if (door->door_state == DOOR_OPENED_UNLOCKED)
	{
		if (config->tex.door_open.img)
			return (&config->tex.door_open);
		return (&config->tex.east);
	}
	return (&config->tex.north);
}

t_interactive	*find_interactive_at(t_config *config, int x, int y)
{
	t_interactive	*current;

	current = config->game_state.interactives;
	while (current)
	{
		if (current->x == x && current->y == y)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	is_wall(t_config *config, int map_x, int map_y)
{
	char	cell;

	if (map_y < 0 || map_y >= config->map_height)
		return (1);
	if (map_x < 0 || map_x >= (int)ft_strlen(config->map[map_y]))
		return (1);
	cell = config->map[map_y][map_x];
	if (cell == '1')
		return (1);
	if (cell == 'L')
		return (1);
	if (cell == 'D')
		return (1);
	return (0);
}

t_texture	*get_wall_texture(t_config *config, int wall_dir)
{
	if (wall_dir == 0)
		return (&config->tex.north);
	else if (wall_dir == 1)
		return (&config->tex.south);
	else if (wall_dir == 2)
		return (&config->tex.east);
	else
		return (&config->tex.west);
}

float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	render_raycast(t_config *config, t_data *img)
{
	int		x;
	float	camera_x;
	float	ray_angle;
	t_ray	ray;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		camera_x = 2 * x / (float)WINDOW_WIDTH - 1;
		ray_angle = normalize_angle(config->player.angle
				+ atan(camera_x * FOV_HALF_TAN));
		ray = dda_cast_ray(config, ray_angle);
		ray.distance = ray.distance * cos(ray_angle - config->player.angle);
		render_textured_wall(config, img, x, ray);
		x++;
	}
}
