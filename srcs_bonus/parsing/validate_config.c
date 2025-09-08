/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:01:08 by nsaillez          #+#    #+#             */
/*   Updated: 2025/09/08 12:02:50 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	all_config_complete(t_parse_state *state)
{
	return (state->north_found && state->south_found
		&& state->west_found && state->east_found
		&& state->floor_found && state->ceiling_found);
}

int	validate_config_completeness(t_config *config)
{
	if (!config->north_texture || !config->south_texture
		|| !config->west_texture || !config->east_texture
		|| !config->floor_texture || !config->ceiling_texture
		|| config->map == NULL)
	{
		cleanup_config(config);
		return (print_error("Missing texture configuration"), 0);
	}
	if (!*config->north_texture || !*config->south_texture
		|| !*config->west_texture || !*config->east_texture
		|| !*config->floor_texture || !*config->ceiling_texture)
	{
		cleanup_config(config);
		return (print_error("Empty texture path"), 0);
	}
	return (1);
}

int	validate_complete_config2(t_config *config, int n_d_txt, int n_l_txt)
{
	t_interactive	*current;

	current = config->game_state.interactives;
	while (current)
	{
		if (current->type == INTERACTIVE_DOOR)
			n_d_txt = 1;
		else if (current->type == INTERACTIVE_LEVER)
			n_l_txt = 1;
		current = current->next;
	}
	if (n_d_txt && (!config->door_locked_texture
			|| !config->door_unlocked_texture || !config->door_open_texture))
		printf("Warning: Doors found in map but door textures not\
			 specified. Using wall textures.\n");
	if (n_l_txt && (!config->lever_off_north_texture
			|| !config->lever_on_north_texture))
		printf("Warning: Levers found in map but lever textures not\
			 specified. Using wall textures.\n");
	if (config->game_state.total_levers == 0 && n_d_txt)
		return (cleanup_config(config), print_error("Map contains\
			 doors but no levers. Add at least one lever (L)."), 0);
	return (1);
}

int	validate_complete_config(t_config *config)
{
	int				n_d_txt;
	int				n_l_txt;

	n_d_txt = 0;
	n_l_txt = 0;
	if (!validate_config_completeness(config))
		return (0);
	if (!validate_all_textures(config))
		return (cleanup_config(config), 0);
	if (!validate_map(config))
		return (cleanup_config(config), 0);
	scan_for_interactive_elements(config);
	return (validate_complete_config2(config, n_d_txt, n_l_txt));
}
