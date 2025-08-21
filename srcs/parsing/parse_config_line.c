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

int	parse_config_line3(char **tokens, t_config *config,
	t_parse_state *state)
{
	if (ft_strncmp(tokens[0], "C", 1) == 0)
	{
		if (!parse_ceiling_color(tokens, config, state))
			return (0);
	}
	ft_free_split(tokens);
	update_config_status(state);
	return (1);
}

int	parse_floor_color(char **tokens, t_config *config,
	t_parse_state *state)
{
	char	**f_rgb;

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
		return (print_error("Invalid RGB format for floor color"), 0);
	}
	affect_rgb(0, config, f_rgb);
	if (!validate_rgb(config->floor_color[0], config->floor_color[1],
			config->floor_color[2]))
	{
		ft_free_split(f_rgb);
		ft_free_split(tokens);
		return (print_error("RGB value must be between 0 and 255"), 0);
	}
	state->floor_found = 1;
	ft_free_split(f_rgb);
	return (1);
}

int	parse_config_line2(char **tokens, t_config *config,
	t_parse_state *state)
{
	if (ft_strncmp(tokens[0], "EA", 2) == 0
		|| ft_strncmp(tokens[0], "E", 1) == 0)
	{
		config->east_texture = ft_strdup(tokens[1]);
		state->east_found = 1;
	}
	else if (ft_strncmp(tokens[0], "F", 1) == 0)
	{
		if (!parse_floor_color(tokens, config, state))
			return (0);
	}
	return (parse_config_line3(tokens, config, state));
}

void	handle_config_line(char *key, char *value, t_config *config,
	t_parse_state *state)
{
	if (!ft_strncmp(key, "NO", 2) || !ft_strncmp(key, "N", 1))
	{
		config->north_texture = ft_strdup(value);
		state->north_found = 1;
	}
	else if (!ft_strncmp(key, "SO", 2) || !ft_strncmp(key, "S", 1))
	{
		config->south_texture = ft_strdup(value);
		state->south_found = 1;
	}
	else if (!ft_strncmp(key, "WE", 2) || !ft_strncmp(key, "W", 1))
	{
		config->west_texture = ft_strdup(value);
		state->west_found = 1;
	}
}

int	parse_config_line(char *line, t_config *config, t_parse_state *state)
{
	char	**tokens;

	tokens = ft_split(line, " \t\n\r");
	if (!tokens || !tokens[0] || !tokens[1])
	{
		ft_free_split(tokens);
		return (0);
	}
	handle_config_line(tokens[0], tokens[1], config, state);
	return (parse_config_line2(tokens, config, state));
}
