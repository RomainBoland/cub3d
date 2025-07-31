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

t_texture *get_lever_texture(t_config *config, t_interactive *lever, int wall_dir)
{
    if (!lever || lever->type != INTERACTIVE_LEVER)
        return (&config->tex.north); // Fallback
    int texture_side;
    if (wall_dir == 0)
        texture_side = 0; // Hit north side -> show south texture
    else if (wall_dir == 1)
        texture_side = 1; // Hit south side -> show north texture
    else
        texture_side = 2; // Hit east/west side -> show base texture
    
    // Return appropriate texture based on lever state and which side we're seeing
    if (lever->is_activated)
    {
        switch (texture_side)
        {
            case 0: // Show north side
                if (config->tex.lever_on_north.img)
                    return (&config->tex.lever_on_north);
                break;
            case 1: // Show south side
                if (config->tex.lever_on_south.img)
                    return (&config->tex.lever_on_south);
                break;
            default: // Show base/side view
                if (config->tex.lever_on_base.img)
                    return (&config->tex.lever_on_base);
                break;
        }
        // Fallback for activated levers
        return (&config->tex.south);
    }
    else
    {
        switch (texture_side)
        {
            case 0: // Show north side
                if (config->tex.lever_off_north.img)
                    return (&config->tex.lever_off_north);
                break;
            case 1: // Show south side
                if (config->tex.lever_off_south.img)
                    return (&config->tex.lever_off_south);
                break;
            default: // Show base/side view
                if (config->tex.lever_off_base.img)
                    return (&config->tex.lever_off_base);
                break;
        }
        // Fallback for inactive levers
        return (&config->tex.west);
    }
}


t_texture *get_door_texture(t_config *config, t_interactive *door)
{
    if (!door || door->type != INTERACTIVE_DOOR)
        return (&config->tex.north); // Fallback
    
    switch (door->door_state)
    {
        case DOOR_CLOSED_LOCKED:
            if (config->tex.door_locked.img)
            {
                return (&config->tex.door_locked);
            }
            return (&config->tex.north); // Fallback to wall texture
        case DOOR_CLOSED_UNLOCKED:
            if (config->tex.door_unlocked.img)
            {
                return (&config->tex.door_unlocked);
            }
            return (&config->tex.south); // Fallback to different wall texture
        case DOOR_OPENED_UNLOCKED:
            if (config->tex.door_open.img)
            {
                return (&config->tex.door_open);
            }
            return (&config->tex.east); // Fallback to different wall texture
        default:
            return (&config->tex.north);
    }
}

t_interactive *find_interactive_at(t_config *config, int x, int y)
{
	t_interactive *current;

	current = config->game_state.interactives;
	while (current)
	{
		if (current->x == x && current->y == y)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int is_wall(t_config *config, int map_x, int map_y)
{
    if (map_y < 0 || map_y >= config->map_height)
        return (1);
    if (map_x < 0 || map_x >= (int)ft_strlen(config->map[map_y]))
        return (1);
    
    char cell = config->map[map_y][map_x];
    
    // Regular walls
    if (cell == '1')
        return (1);
    
    // Levers act like walls (not walkable)
    if (cell == 'L')
        return (1);
    
    // Check doors
    if (cell == 'D')
		return (1);
		
    return (0);  // Everything else is passable
}

t_texture *get_wall_texture(t_config *config, int wall_dir)
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
