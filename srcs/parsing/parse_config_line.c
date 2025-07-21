/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:03:35 by rboland           #+#    #+#             */
/*   Updated: 2025/07/18 10:03:35 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void affect_rgb(int marker, t_config *config, char **rgb)
{
	if (marker == 0) // Floor
	{
		config->floor_color[0] = atoi(rgb[0]);
		config->floor_color[1] = atoi(rgb[1]);
		config->floor_color[2] = atoi(rgb[2]);
	}
	else if (marker == 1) // Ceiling
	{
		config->ceiling_color[0] = atoi(rgb[0]);
		config->ceiling_color[1] = atoi(rgb[1]);
		config->ceiling_color[2] = atoi(rgb[2]);
	}
}

int validate_rgb(int r, int g, int b)
{
    return (r >= 0 && r <= 255 && 
            g >= 0 && g <= 255 && 
            b >= 0 && b <= 255);
}

int parse_config_line3(char **tokens, t_config *config, t_parse_state *state)
{
	char **c_rgb;

	if (ft_strncmp(tokens[0], "C", 1) == 0)
	{
		if (!is_valid_tab_format(tokens))
		{
			ft_free_split(tokens);
			return (print_error("Invalid RGB format for ceiling color"), 0);
		}
		c_rgb = ft_split(tokens[1], ", \t");
		if (!c_rgb || !c_rgb[0] || !c_rgb[1] || !c_rgb[2])
		{
			ft_free_split(tokens);
			ft_free_split(c_rgb);
			return (0);
		}
		affect_rgb(1, config, c_rgb);
		if (!validate_rgb(config->ceiling_color[0], config->ceiling_color[1], config->ceiling_color[2]))
		{
			ft_free_split(c_rgb);
			return (0);
		}
		state->ceiling_found = 1;
		ft_free_split(c_rgb);
	}
	ft_free_split(tokens);
	state->all_config_found = state->north_found && state->south_found &&
							  state->west_found && state->east_found &&
							  state->floor_found && state->ceiling_found;
	return (1);
}

int parse_config_line2(char **tokens, t_config *config, t_parse_state *state)
{
	char **f_rgb;
	
	if (ft_strncmp(tokens[0], "EA", 2) == 0 || ft_strncmp(tokens[0], "E", 1) == 0)
	{
		config->east_texture = ft_strdup(tokens[1]);
		state->east_found = 1;
	}
	else if (ft_strncmp(tokens[0], "F", 1) == 0)
	{
		if (!is_valid_tab_format(tokens))
		{
			ft_free_split(tokens);
			return (print_error("Invalid RGB format for floor color"), 0);
		}
		f_rgb = ft_split(tokens[1], ", \t");
		if (!f_rgb || !f_rgb[0] || !f_rgb[1] || !f_rgb[2])
		{
			ft_free_split(tokens);
			ft_free_split(f_rgb);
			return (0);
		}
		affect_rgb(0, config, f_rgb);
		if (!validate_rgb(config->floor_color[0], config->floor_color[1], config->floor_color[2]))
		{
			ft_free_split(f_rgb);
			return (0);
		}
		state->floor_found = 1;
		ft_free_split(f_rgb);
	}
	return (parse_config_line3(tokens, config, state));
}

int parse_config_line(char *line, t_config *config, t_parse_state *state)
{
	char **tokens;

	tokens = ft_split(line, " \t\n\r");
	if (!tokens || !tokens[0] || !tokens[1])
	{
		ft_free_split(tokens);
		return (0);
	}
	if ((ft_strncmp(tokens[0], "NO", 2) == 0 || ft_strncmp(tokens[0], "N", 1) == 0))
	{
		config->north_texture = ft_strdup(tokens[1]);
		state->north_found = 1;
	}
	else if ((ft_strncmp(tokens[0], "SO", 2) == 0 || ft_strncmp(tokens[0], "S", 1) == 0))
	{
		config->south_texture = ft_strdup(tokens[1]);
		state->south_found = 1;
	}
	else if ((ft_strncmp(tokens[0], "WE", 2) == 0 || ft_strncmp(tokens[0], "W", 1) == 0))
	{
		config->west_texture = ft_strdup(tokens[1]);
		state->west_found = 1;
	}
	return (parse_config_line2(tokens, config, state));
}
