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

#include "cub3d.h"

int	is_config_line(const char *line)
{
	return (ft_strncmp(line, "N", 1) == 0 ||
			ft_strncmp(line, "S", 1) == 0 ||
			ft_strncmp(line, "W", 1) == 0 ||
			ft_strncmp(line, "E", 1) == 0 ||
			ft_strncmp(line, "F ", 2) == 0 ||
			ft_strncmp(line, "C ", 2) == 0);
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

int is_map_line(const char *line)
{
    while (*line)
    {
        if (*line != '1' && *line != '0' && *line != 'N' &&
            *line != 'S' && *line != 'E' && *line != 'W' &&
            !ft_isspace((unsigned char)*line))
            return (0);
        line++;
    }
    return (1);
}

int all_config_complete(t_parse_state *state)
{
	return (state->north_found && state->south_found &&
			state->west_found && state->east_found &&
			state->floor_found && state->ceiling_found);
}

void print_map(char **map, int width, int height)
{
	int i;

	printf("Map (%d x %d):\n", width, height);
	for (i = 0; i < height; i++)
	{
		if (map[i])
			printf("%s", map[i]);
		else
			printf("(null)\n");
	}
	printf("\n");
}

int validate_complete_config(t_config *config)
{
	if (!config->north_texture || !config->south_texture ||
		!config->west_texture || !config->east_texture ||
		config->floor_color[0] < 0 || config->floor_color[1] < 0 ||
		config->floor_color[2] < 0 || config->ceiling_color[0] < 0 ||
		config->ceiling_color[1] < 0 || config->ceiling_color[2] < 0 ||
		config->map == NULL)
	{
		cleanup_config(config);
		return (print_error("Incomplete configuration"), 0);
	}
	print_map(config->map, config->map_width, config->map_height);
	return (1);
}
