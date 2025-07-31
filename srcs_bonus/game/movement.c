/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:10:49 by rboland           #+#    #+#             */
/*   Updated: 2025/07/22 11:10:49 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int is_movement_blocked(t_config *config, float x, float y)
{
    int map_x = (int)x;
    int map_y = (int)y;
    
    if (map_y < 0 || map_y >= config->map_height)
        return (1);
    if (map_x < 0 || map_x >= (int)ft_strlen(config->map[map_y]))
        return (1);
    
    char cell = config->map[map_y][map_x];
    
    // Regular walls block movement
    if (cell == '1')
        return (1);
    
    // Levers block movement
    if (cell == 'L')
        return (1);
    
    // Only CLOSED doors block movement
    if (cell == 'D')
    {
        t_interactive *door = find_interactive_at(config, map_x, map_y);
        if (door && door->door_state == DOOR_OPENED_UNLOCKED)
            return (0);  // Open doors don't block movement
        return (1);      // Closed doors block movement
    }
    
    return (0);  // Everything else is passable
}

// int	is_valid_position(t_config *config, float x, float y)
// {
// 	int	map_x;
// 	int	map_y;

// 	map_x = (int)x;
// 	map_y = (int)y;
// 	if (map_y < 0 || map_y >= config->map_height)
// 		return (0);
// 	if (map_x < 0 || map_x >= (int)ft_strlen(config->map[map_y]))
// 		return (0);
// 	if (config->map[map_y][map_x] == '1')
// 		return (0);
// 	return (1);
// }

void	change_pitch(t_config *config, float pitch_change)
{
	config->player.pitch += pitch_change;
	if (config->player.pitch > MAX_PITCH)
		config->player.pitch = MAX_PITCH;
	else if (config->player.pitch < -MAX_PITCH)
		config->player.pitch = -MAX_PITCH;
}

void	move_player(t_config *config, float move_x, float move_y)
{
	float	new_x;
	float	new_y;

	new_x = config->player.pos_x + move_x;
	new_y = config->player.pos_y + move_y;
	if (!is_movement_blocked(config, new_x, config->player.pos_y))
		config->player.pos_x = new_x;
	if (!is_movement_blocked(config, config->player.pos_x, new_y))
		config->player.pos_y = new_y;
	config->player.x = (int)config->player.pos_x;
	config->player.y = (int)config->player.pos_y;
}

void	rotate_player(t_config *config, float rotation)
{
	config->player.angle += rotation;
	if (config->player.angle < 0)
		config->player.angle += 2 * PI;
	else if (config->player.angle >= 2 * PI)
		config->player.angle -= 2 * PI;
}
