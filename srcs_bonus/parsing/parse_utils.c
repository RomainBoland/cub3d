/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:11:09 by rboland           #+#    #+#             */
/*   Updated: 2025/07/18 10:11:09 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int is_config_line(const char *line)
{
    return (ft_strncmp(line, "N ", 2) == 0
        || ft_strncmp(line, "S ", 2) == 0
        || ft_strncmp(line, "W ", 2) == 0
        || ft_strncmp(line, "E ", 2) == 0
        || ft_strncmp(line, "NO ", 3) == 0
        || ft_strncmp(line, "SO ", 3) == 0
        || ft_strncmp(line, "EA ", 3) == 0
        || ft_strncmp(line, "WE ", 3) == 0
        || ft_strncmp(line, "F ", 2) == 0
        || ft_strncmp(line, "C ", 2) == 0
        || ft_strncmp(line, "DL ", 3) == 0
        || ft_strncmp(line, "DU ", 3) == 0
        || ft_strncmp(line, "DO ", 3) == 0
        || ft_strncmp(line, "LON ", 4) == 0
        || ft_strncmp(line, "LOS ", 4) == 0
        || ft_strncmp(line, "LOB ", 4) == 0
        || ft_strncmp(line, "LNN ", 4) == 0
        || ft_strncmp(line, "LNS ", 4) == 0
        || ft_strncmp(line, "LNB ", 4) == 0);
}

int	is_empty_line(const char *line)
{
	while (*line)
	{
		if (!ft_isspace((int)*line))
			return (0);
		line++;
	}
	return (1);
}

int	all_config_complete(t_parse_state *state)
{
	return (state->north_found && state->south_found
		&& state->west_found && state->east_found
		&& state->floor_found && state->ceiling_found);
}

static int	validate_config_completeness(t_config *config)
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

int validate_complete_config(t_config *config)
{
    if (!validate_config_completeness(config))
        return (0);
    if (!validate_all_textures(config))
    {
        cleanup_config(config);
        return (0);
    }
    if (!validate_map(config))
    {
        cleanup_config(config);
        return (0);
    }
    
    // Scan for interactive elements after map validation
    scan_for_interactive_elements(config);
    
    // Check interactive texture requirements
    t_interactive *current = config->game_state.interactives;
    int needs_door_textures = 0;
    int needs_lever_textures = 0;
    
    while (current)
    {
        if (current->type == INTERACTIVE_DOOR)
            needs_door_textures = 1;
        else if (current->type == INTERACTIVE_LEVER)
            needs_lever_textures = 1;
        current = current->next;
    }
    
    // Warn if interactive elements exist but textures aren't provided
    if (needs_door_textures && (!config->door_locked_texture || 
        !config->door_unlocked_texture || !config->door_open_texture))
    {
        printf("Warning: Doors found in map but door textures not specified. Using wall textures.\n");
    }
    
    if (needs_lever_textures && (!config->lever_off_north_texture || 
        !config->lever_on_north_texture))
    {
        printf("Warning: Levers found in map but lever textures not specified. Using wall textures.\n");
    }
    
    // Validate that we have at least one door and one lever if interactive mode
    if (config->game_state.total_levers == 0 && needs_door_textures)
    {
        cleanup_config(config);
        return (print_error("Map contains doors but no levers. Add at least one lever (L)."), 0);
    }
    
    return (1);
}
