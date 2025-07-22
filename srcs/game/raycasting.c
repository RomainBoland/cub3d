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

int is_wall(t_config *config, int map_x, int map_y)
{
    // Remove the debug printf that was spamming
    if (map_y < 0 || map_y >= config->map_height)
        return (1);
    if (map_x < 0 || map_x >= (int)ft_strlen(config->map[map_y]))
        return (1);
    return (config->map[map_y][map_x] == '1');
}

t_ray dda_cast_ray(t_config *config, float ray_angle)
{
    t_ray result = {0};
    
    // Ray direction
    float ray_dir_x = cos(ray_angle);
    float ray_dir_y = sin(ray_angle);

    // Current ray position
    float ray_x = config->player.pos_x;
    float ray_y = config->player.pos_y;

    // Which grid cell we're in
    int map_x = (int)ray_x;
    int map_y = (int)ray_y;

    // Length of ray from current position to x or y side
    float side_dist_x;
    float side_dist_y;

    // Prevent division by zero
	float delta_dist_x;
	if (ray_dir_x == 0)
		delta_dist_x = 1e30;
	else
		delta_dist_x = fabs(1 / ray_dir_x);

	float delta_dist_y;
	if (ray_dir_y == 0)
		delta_dist_y = 1e30;
	else
		delta_dist_y = fabs(1 / ray_dir_y);

    // Which direction to step in
    int step_x;
    int step_y;

    // Calculate step and initial side_dist
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

    // DDA algorithm
    int hit = 0;
    int side;

    while (hit == 0)
    {
        // Jump to next grid intersection
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
        
        if (is_wall(config, map_x, map_y))
            hit = 1;
    }

    // Calculate distance
    float perp_wall_dist;
    if (side == 0) // vertical wall
    {
        perp_wall_dist = (map_x - ray_x + (1 - step_x) / 2) / ray_dir_x;
        result.wall_x = ray_y + perp_wall_dist * ray_dir_y;
        // Determine wall direction for texture selection
        if (step_x == 1)
			result.wall_dir = 3; // West
		else
			result.wall_dir = 2; // East
    }
    else // horizontal wall
    {
        perp_wall_dist = (map_y - ray_y + (1 - step_y) / 2) / ray_dir_y;
        result.wall_x = ray_x + perp_wall_dist * ray_dir_x;
        // Determine wall direction for texture selection
		if (step_y == 1)
			result.wall_dir = 0; // North
		else
			result.wall_dir = 1; // South
    }
    
    result.wall_x = result.wall_x - floor(result.wall_x); // Get fractional part
    if (result.wall_x < 0)
		result.wall_x += 1.0;
    
	if (perp_wall_dist <= 0)
		result.distance = 0.1;
	else
		result.distance = perp_wall_dist;
    result.side = side;
    
    return (result);
}

t_texture *get_wall_texture(t_config *config, int wall_dir)
{
    if (wall_dir == 0) // North
        return (&config->tex.north);
    else if (wall_dir == 1) // South
        return (&config->tex.south);
    else if (wall_dir == 2) // East
        return (&config->tex.east);
    else // West
        return (&config->tex.west);
}

void render_textured_wall(t_config *config, t_data *img, int x, t_ray ray)
{
    int f_color = (config->floor_color[0] << 16) | (config->floor_color[1] << 8) | config->floor_color[2];
    int c_color = (config->ceiling_color[0] << 16) | (config->ceiling_color[1] << 8) | config->ceiling_color[2];
    
    // Calculate wall height - ADD MAXIMUM LIMIT
    int wall_height = (int)(WINDOW_HEIGHT / ray.distance);
    if (wall_height > WINDOW_HEIGHT * 3)  // Limit maximum wall height
        wall_height = WINDOW_HEIGHT * 3;
    if (wall_height < 1)
        wall_height = 1;
    
    int wall_start = (WINDOW_HEIGHT - wall_height) / 2;
    int wall_end = wall_start + wall_height;
    
    // Clamp values to screen bounds
    int draw_start;
	if (wall_start < 0)
		draw_start = 0;
	else
		draw_start = wall_start;
	int draw_end;
	if (wall_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	else
		draw_end = wall_end;
    
    // Get the appropriate texture
    t_texture *texture = get_wall_texture(config, ray.wall_dir);
    
    // Calculate texture X coordinate
    int tex_x = (int)(ray.wall_x * texture->width);
    if (tex_x >= texture->width) tex_x = texture->width - 1;
    if (tex_x < 0) tex_x = 0;
    
    // Draw ceiling
    for (int y = 0; y < draw_start; y++)
        my_mlx_pixel_put(img, x, y, c_color);
    
    // FIXED TEXTURE CALCULATION - prevents overflow and distortion
    float step = (float)texture->height / wall_height;  // How much to increase tex_y per pixel
    float tex_pos = 0.0;
    
    // If wall starts above screen, adjust starting texture position
    if (wall_start < 0)
        tex_pos = (-wall_start) * step;
    
    // Draw textured wall
    for (int y = draw_start; y <= draw_end; y++)
    {
        // Calculate texture Y coordinate using floating point precision
        int tex_y = (int)tex_pos;
        
        // Ensure tex_y is within bounds
        if (tex_y >= texture->height) tex_y = texture->height - 1;
        if (tex_y < 0) tex_y = 0;
        
        // Get pixel color from texture
        unsigned int color = get_texture_pixel(texture, tex_x, tex_y);
        
        // OPTIONAL: Apply distance-based shading (remove if you don't want shadows)
        if (ray.distance > 5.0)
        {
            int r = (color >> 16) & 0xFF;
            int g = (color >> 8) & 0xFF;
            int b = color & 0xFF;
            
            float shade = 1.0 - (ray.distance - 5.0) / 15.0;  // Made falloff more gradual
            if (shade < 0.4) shade = 0.5; // Don't make it too dark
            if (shade > 1.0) shade = 1.0;
            
            r = (int)(r * shade);
            g = (int)(g * shade);
            b = (int)(b * shade);
            
            color = (r << 16) | (g << 8) | b;
        }
        
        my_mlx_pixel_put(img, x, y, color);
        
        // Move to next texture pixel
        tex_pos += step;
    }
    
    // Draw floor
    for (int y = draw_end + 1; y < WINDOW_HEIGHT; y++)
        my_mlx_pixel_put(img, x, y, f_color);
}

float normalize_angle(float angle)
{
    while (angle < 0)
        angle += 2 * PI;
    while (angle >= 2 * PI)
        angle -= 2 * PI;
    return angle;
}

void render_raycast(t_config *config, t_data *img)
{
    for (int x = 0; x < WINDOW_WIDTH; x++)
    {
        // Calculate camera X coordinate (-1 to 1)
        float camera_x = 2 * x / (float)WINDOW_WIDTH - 1;
        
        // Calculate ray angle with 60-degree FOV
        float ray_angle = normalize_angle(config->player.angle + atan(camera_x * tan(PI / 6)));
        
        // Cast ray and get detailed information
        t_ray ray = dda_cast_ray(config, ray_angle);
        
        // Apply fish-eye correction
        ray.distance = ray.distance * cos(ray_angle - config->player.angle);
        
        // Render the textured wall column
        render_textured_wall(config, img, x, ray);
    }
}
