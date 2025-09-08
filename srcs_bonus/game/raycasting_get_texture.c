/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_get_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:37:00 by nsaillez          #+#    #+#             */
/*   Updated: 2025/09/08 09:37:55 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
