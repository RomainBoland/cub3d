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

int parse_config_line3(char **tokens, t_config *config, t_parse_state *state, char **rgb)
{
	if (ft_strncmp(tokens[0], "C", 1) == 0)
	{
		rgb = ft_split(tokens[1], ',');
		if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		{
			ft_free_split(tokens);
			ft_free_split(rgb);
			return (0);
		}
		printf("Parsing ceiling color: %s %s %s\n", rgb[0], rgb[1], rgb[2]);
		affect_rgb(1, config, rgb);
		if (!validate_rgb(config->ceiling_color[0], config->ceiling_color[1], config->ceiling_color[2]))
		{
			printf("Invalid RGB values for ceiling color\n");
			ft_free_split(rgb);
			return (0);
		}
		state->ceiling_found = 1;
	}
	if (ft_strncmp(tokens[0], "C", 1) == 0 || ft_strncmp(tokens[0], "F", 1) == 0)
		ft_free_split(rgb);
	ft_free_split(tokens);
	state->all_config_found = state->north_found && state->south_found &&
							  state->west_found && state->east_found &&
							  state->floor_found && state->ceiling_found;
	return (1);
}

int parse_config_line2(char **tokens, t_config *config, t_parse_state *state)
{
	char **rgb;
	
	if (ft_strncmp(tokens[0], "EA", 2) == 0 || ft_strncmp(tokens[0], "E", 1) == 0)
	{
		printf("Parsing east texture: %s %s\n", tokens[0], tokens[1]);
		config->east_texture = ft_strdup(tokens[1]);
		state->east_found = 1;
	}
	else if (ft_strncmp(tokens[0], "F", 1) == 0)
	{
		rgb = ft_split(tokens[1], ',');
		if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		{
			ft_free_split(tokens);
			ft_free_split(rgb);
			return (0);
		}
		printf("Parsing floor color: %s %s %s\n", rgb[0], rgb[1], rgb[2]);
		affect_rgb(0, config, rgb);
		if (!validate_rgb(config->floor_color[0], config->floor_color[1], config->floor_color[2]))
		{
			printf("Invalid RGB values for floor color\n");
			ft_free_split(rgb);
			return (0);
		}
		state->floor_found = 1;
	}
	return (parse_config_line3(tokens, config, state, rgb));
}

int parse_config_line(char *line, t_config *config, t_parse_state *state)
{
	char **tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
	{
		ft_free_split(tokens);
		return (0);
	}
	if ((ft_strncmp(tokens[0], "NO", 2) == 0 || ft_strncmp(tokens[0], "N", 1) == 0))
	{
		printf("Parsing north texture: %s %s\n", tokens[0], tokens[1]);
		config->north_texture = ft_strdup(tokens[1]);
		state->north_found = 1;
		printf("North texture set: %s\n", config->north_texture);
	}
	else if ((ft_strncmp(tokens[0], "SO", 2) == 0 || ft_strncmp(tokens[0], "S", 1) == 0))
	{
		printf("Parsing south texture: %s %s\n", tokens[0], tokens[1]);
		config->south_texture = ft_strdup(tokens[1]);
		state->south_found = 1;
	}
	else if ((ft_strncmp(tokens[0], "WE", 2) == 0 || ft_strncmp(tokens[0], "W", 1) == 0))
	{
		printf("Parsing west texture: %s %s\n", tokens[0], tokens[1]);
		config->west_texture = ft_strdup(tokens[1]);
		state->west_found = 1;
	}
	return (parse_config_line2(tokens, config, state));
}
