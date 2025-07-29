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

int	is_config_line(const char *line)
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
		|| ft_strncmp(line, "C ", 2) == 0);
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

int	validate_complete_config(t_config *config)
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
	return (1);
}
