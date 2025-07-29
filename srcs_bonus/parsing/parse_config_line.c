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

#include "cub3d_bonus.h"

void	update_config_status(t_parse_state *state)
{
	state->all_config_found = state->north_found && state->south_found
		&& state->west_found && state->east_found
		&& state->floor_found && state->ceiling_found;
}

static void	handle_config_line2(char *key, char *value, t_config *config,
	t_parse_state *state)
{
	if (ft_strncmp(key, "EA", 2) == 0
		|| ft_strncmp(key, "E", 1) == 0)
	{
		config->east_texture = ft_strdup(value);
		state->east_found = 1;
	}
    else if (!ft_strncmp(key, "F", 1))
    {
        config->floor_texture = ft_strdup(value);
        state->floor_found = 1;
    }
    else if (!ft_strncmp(key, "C", 1))
    {
        config->ceiling_texture = ft_strdup(value);
        state->ceiling_found = 1;
	}
}

static void	handle_config_line(char *key, char *value, t_config *config,
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
	handle_config_line2(tokens[0], tokens[1], config, state);
	ft_free_split(tokens);
	return (1);
}
