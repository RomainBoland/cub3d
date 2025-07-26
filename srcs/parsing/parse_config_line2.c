/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_line2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:14:45 by rboland           #+#    #+#             */
/*   Updated: 2025/07/26 16:14:45 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	affect_rgb(int marker, t_config *config, char **rgb)
{
	if (marker == 0)
	{
		config->floor_color[0] = atoi(rgb[0]);
		config->floor_color[1] = atoi(rgb[1]);
		config->floor_color[2] = atoi(rgb[2]);
	}
	else if (marker == 1)
	{
		config->ceiling_color[0] = atoi(rgb[0]);
		config->ceiling_color[1] = atoi(rgb[1]);
		config->ceiling_color[2] = atoi(rgb[2]);
	}
}

int	validate_rgb(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

int	parse_ceiling_color(char **tokens, t_config *config,
	t_parse_state *state)
{
	char	**c_rgb;

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
	if (!validate_rgb(config->ceiling_color[0], config->ceiling_color[1],
			config->ceiling_color[2]))
	{
		ft_free_split(c_rgb);
		return (print_error("RGB value must be between 0 and 255"), 0);
	}
	state->ceiling_found = 1;
	ft_free_split(c_rgb);
	return (1);
}

void	update_config_status(t_parse_state *state)
{
	state->all_config_found = state->north_found && state->south_found
		&& state->west_found && state->east_found
		&& state->floor_found && state->ceiling_found;
}
