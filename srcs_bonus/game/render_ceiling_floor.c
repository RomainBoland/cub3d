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

static unsigned int get_safe_texture_pixel(t_texture *texture, int x, int y)
{
    x = x & (texture->width - 1);
    y = y & (texture->height - 1);
    return get_texture_pixel(texture, x, y);
}

static float	abs_val(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

static float fast_distance_approximation(float dx, float dy)
{
    float abs_dx;
    float abs_dy;

	abs_dx = abs_val(dx);
	abs_dy = abs_val(dy);
    if (abs_dx > abs_dy)
        return abs_dx + 0.5f * abs_dy;
    else
        return abs_dy + 0.5f * abs_dx;
}

// Optimized world position calculation (no static variables)
static void calculate_world_position(t_config *config, int screen_x, int screen_y, 
                                               float cos_angle, float sin_angle,
                                               float plane_x, float plane_y,
                                               float *world_x, float *world_y, float *distance)
{
    // Camera coordinate (reuse calculation)
    float camera_x = 2.0f * screen_x / (float)WINDOW_WIDTH - 1.0f;
    
    // Ray direction
    float ray_dir_x = cos_angle + plane_x * camera_x;
    float ray_dir_y = sin_angle + plane_y * camera_x;
    
    // Row distance calculation (simplified)
    float row_distance;
    if (screen_y > WINDOW_HEIGHT / 2) {
        row_distance = (0.5f * WINDOW_HEIGHT) / (screen_y - WINDOW_HEIGHT / 2);
    } else {
        row_distance = (0.5f * WINDOW_HEIGHT) / (WINDOW_HEIGHT / 2 - screen_y);
    }
    
    // World position
    *world_x = config->player.pos_x + row_distance * ray_dir_x;
    *world_y = config->player.pos_y + row_distance * ray_dir_y;
    *distance = row_distance; // Use row_distance as approximation
}

void render_floor_ceiling_column(t_config *config, t_data *img, int x, 
                                  int wall_start, int wall_end)
{
    int y;
    float world_x, world_y, distance;
    int tex_x, tex_y;
    unsigned int color;
    float dx, dy;
    
    // Pre-calculate trigonometric values once per column
    float cos_angle = cos(config->player.angle);
    float sin_angle = sin(config->player.angle);
    float plane_x = -sin_angle * FOV_HALF_TAN;
    float plane_y = cos_angle * FOV_HALF_TAN;
    
    // Render ceiling
    for (y = 0; y < wall_start; y++) {
        calculate_world_position(config, x, y, cos_angle, sin_angle,
                                    plane_x, plane_y, &world_x, &world_y, &distance);
        
        tex_x = (int)(world_x * config->tex.ceiling.width);
        tex_y = (int)(world_y * config->tex.ceiling.height);
        
        color = get_safe_texture_pixel(&config->tex.ceiling, tex_x, tex_y);
        
        // Use fast distance approximation instead of sqrt
        dx = world_x - config->player.pos_x;
        dy = world_y - config->player.pos_y;
        distance = fast_distance_approximation(dx, dy);
        
        color = apply_distance_shading(color, distance);
        my_mlx_pixel_put(img, x, y, color);
    }
    
    // Render floor
    for (y = wall_end + 1; y < WINDOW_HEIGHT; y++) {
        calculate_world_position(config, x, y, cos_angle, sin_angle,
                                    plane_x, plane_y, &world_x, &world_y, &distance);
        
        tex_x = (int)(world_x * config->tex.floor.width);
        tex_y = (int)(world_y * config->tex.floor.height);
        
        color = get_safe_texture_pixel(&config->tex.floor, tex_x, tex_y);
        
        // Use fast distance approximation
        dx = world_x - config->player.pos_x;
        dy = world_y - config->player.pos_y;
        distance = fast_distance_approximation(dx, dy);
        
        color = apply_distance_shading(color, distance);
        my_mlx_pixel_put(img, x, y, color);
    }
}
