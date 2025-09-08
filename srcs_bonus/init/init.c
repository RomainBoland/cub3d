/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:10:11 by rboland           #+#    #+#             */
/*   Updated: 2025/07/17 16:10:11 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_config(t_config *config)
{
	config->north_texture = NULL;
	config->south_texture = NULL;
	config->west_texture = NULL;
	config->east_texture = NULL;
	config->floor_texture = NULL;
	config->ceiling_texture = NULL;
	config->door_locked_texture = NULL;
	config->door_unlocked_texture = NULL;
	config->door_open_texture = NULL;
	config->lever_off_north_texture = NULL;
	config->lever_off_south_texture = NULL;
	config->lever_off_base_texture = NULL;
	config->lever_on_north_texture = NULL;
	config->lever_on_south_texture = NULL;
	config->lever_on_base_texture = NULL;
	config->map = NULL;
	config->map_width = 0;
	config->map_height = 0;
	config->game_state.total_levers = 0;
	config->game_state.activated_levers = 0;
	config->game_state.game_won = 0;
	config->game_state.interactives = NULL;
}

void	init_parse_state(t_parse_state *state)
{
	state->north_found = 0;
	state->south_found = 0;
	state->west_found = 0;
	state->east_found = 0;
	state->floor_found = 0;
	state->ceiling_found = 0;
	state->all_config_found = 0;
}
