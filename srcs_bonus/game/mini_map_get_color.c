/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_get_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:28:52 by nsaillez          #+#    #+#             */
/*   Updated: 2025/09/08 10:21:09 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned int	get_door_color(t_interactive *interactive)
{
	if (interactive->door_state == DOOR_CLOSED_LOCKED)
		return (COLOR_DOOR_LOCKED);
	if (interactive->door_state == DOOR_CLOSED_UNLOCKED)
		return (COLOR_DOOR_UNLOCKED);
	if (interactive->door_state == DOOR_OPENED_UNLOCKED)
		return (COLOR_DOOR_OPEN);
	return (COLOR_WALL);
}

unsigned int	get_lever_color(t_interactive *interactive)
{
	if (interactive->is_activated)
		return (COLOR_LEVER_ON);
	return (COLOR_LEVER_OFF);
}

unsigned int	get_interactive_color(t_config *config,
	int map_x, int map_y)
{
	t_interactive	*interactive;
	char			cell;

	cell = config->map[map_y][map_x];
	interactive = find_interactive_at(config, map_x, map_y);
	if (!interactive)
		return (COLOR_WALL);
	if (cell == 'D')
		return (get_door_color(interactive));
	if (cell == 'L')
		return (get_lever_color(interactive));
	return (COLOR_WALL);
}

unsigned int	get_map_cell_color(t_config *config, int map_x, int map_y)
{
	char	cell;

	if (map_y < 0 || map_y >= config->map_height)
		return (COLOR_BACKGROUND);
	if (map_x < 0 || map_x >= (int)ft_strlen(config->map[map_y]))
		return (COLOR_BACKGROUND);
	cell = config->map[map_y][map_x];
	if (cell == '1')
		return (COLOR_WALL);
	if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
		return (COLOR_EMPTY);
	if (cell == 'D' || cell == 'L')
		return (get_interactive_color(config, map_x, map_y));
	return (COLOR_BACKGROUND);
}

unsigned int	get_current_pixel_color(t_game *game, int x, int y)
{
	char	*pixel_addr;

	pixel_addr = game->img.addr + ((y + MINIMAP_OFFSET_Y)
			* game->img.line_length + (x + MINIMAP_OFFSET_X)
			* (game->img.bits_per_pixel / 8));
	return (*(unsigned int *)pixel_addr);
}
