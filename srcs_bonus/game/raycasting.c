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
