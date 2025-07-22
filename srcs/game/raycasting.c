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

#include "cub3d.h"

int	is_wall(t_config *config, int map_x, int map_y)
{
	// Check Y bounds FIRST - this is critical!
	if (map_y < 0 || map_y >= config->map_height)
		return (1);
	
	// Now it's safe to check X bounds
	if (map_x < 0 || map_x >= (int)ft_strlen(config->map[map_y]))
		return (1);
	
	return (config->map[map_y][map_x] == '1');
}

float	dda_cast_ray(t_config *config, float ray_angle)
{
	// direction du rayon
	float ray_dir_x = cos(ray_angle);
	float ray_dir_y = sin(ray_angle);

	// position actuelle du rayon
	float ray_x = config->player.pos_x;
	float ray_y = config->player.pos_y;

	// Quelle case du grid on est
	int map_x = (int)ray_x;
	int map_y = (int)ray_y;

	// Longueur du rayon de la position actuelle en x ou y
	float side_dist_x;
	float side_dist_y;

	// Prevent division by zero
	float delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
	float delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

	// Quelle direction on avance ?
	int step_x;
	int step_y;

	// calculer le prochain pas et la distance initiale
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (ray_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - ray_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (ray_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - ray_y) * delta_dist_y;
	}

	
	int hit = 0;
	int side;
	int max_iterations = config->map_width + config->map_height;

	while (hit == 0 && max_iterations > 0)
	{
		// jump vers la prochaine intersection
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0; // vertical wall
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1; // horizontal wall
		}
		
		// Check for wall hit with proper bounds checking
		if (is_wall(config, map_x, map_y))
			hit = 1;
		
		max_iterations--;
	}

	// Calculate perpendicular wall distance
	float perp_wall_dist;
	if (side == 0) // vertical wall
		perp_wall_dist = (map_x - ray_x + (1 - step_x) / 2) / ray_dir_x;
	else // horizontal wall
		perp_wall_dist = (map_y - ray_y + (1 - step_y) / 2) / ray_dir_y;
	
	// Ensure we don't return negative or zero distances
	if (perp_wall_dist <= 0)
		perp_wall_dist = 0.1;
	
	return perp_wall_dist;
}

float normalize_angle(float angle)
{
    while (angle < 0)
        angle += 2 * PI;
    while (angle >= 2 * PI)
        angle -= 2 * PI;
    return angle;
}

void	render_raycast(t_config *config, t_data *img)
{
	int	f_color;
	int	c_color;
	int	x;

	f_color = (config->floor_color[0] << 16) | (config->floor_color[1] << 8) | config->floor_color[2];
	c_color = (config->ceiling_color[0] << 16) | (config->ceiling_color[1] << 8) | config->ceiling_color[2];
	x = 0;

	while (x < WINDOW_WIDTH)
	{
		// Calculate camera X coordinate (-1 to 1)
		float camera_x = 2 * x / (float)WINDOW_WIDTH - 1;
		
		// Calculate ray angle with proper FOV
		float ray_angle = normalize_angle(config->player.angle + atan(camera_x * tan(PI / 4))); // 60 degree FOV
		
		// Normalize angle to [0, 2π]
		while (ray_angle < 0)
			ray_angle += 2 * PI;
		while (ray_angle >= 2 * PI)
			ray_angle -= 2 * PI;

		// Cast ray and get distance
		float distance = dda_cast_ray(config, ray_angle);
		
		// Apply fish-eye correction
		distance = distance * cos(ray_angle - config->player.angle);

		// Calculate wall height
		int wall_height = (int)(WINDOW_HEIGHT / distance);
		if (wall_height > WINDOW_HEIGHT)
			wall_height = WINDOW_HEIGHT;
		
		int wall_start = (WINDOW_HEIGHT - wall_height) / 2;
		int wall_end = wall_start + wall_height;
		
		// Clamp values to screen bounds
		if (wall_start < 0) wall_start = 0;
		if (wall_end >= WINDOW_HEIGHT) wall_end = WINDOW_HEIGHT - 1;

		// Draw ceiling
		for (int y = 0; y < wall_start; y++)
			my_mlx_pixel_put(img, x, y, c_color);
		
		// Draw wall
		for (int y = wall_start; y <= wall_end; y++)
			my_mlx_pixel_put(img, x, y, 0x808080); // Gray
		
		// Draw floor
		for (int y = wall_end + 1; y < WINDOW_HEIGHT; y++)
			my_mlx_pixel_put(img, x, y, f_color);
		
		x++;
	}
}
