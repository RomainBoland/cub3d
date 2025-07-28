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
	config->map = NULL;
	config->map_width = 0;
	config->map_height = 0;
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
