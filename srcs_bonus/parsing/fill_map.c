/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:19:42 by rboland           #+#    #+#             */
/*   Updated: 2025/07/26 16:19:42 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_map_line(const char *line)
{
	while (*line)
	{
		if (*line != '1' && *line != '0' && *line != 'N'
			&& *line != 'S' && *line != 'E' && *line != 'W'
			&& !ft_isspace((unsigned char)*line))
			return (0);
		line++;
	}
	return (1);
}

static char	**fill_map_array(t_config *config, int old_size, char **new_map)
{
	int		j;

	j = 0;
	while (j < old_size)
	{
		new_map[j] = config->map[j];
		j++;
	}
	return (new_map);
}

int	add_line_to_map(const char *line, t_config *config)
{
	char	**new_map;
	char	*normalized;
	int		i;

	normalized = normalize_line(line);
	if (!normalized)
		return (0);
	i = 0;
	while (config->map[i])
		i++;
	new_map = malloc(sizeof(char *) * (i + 2));
	if (!new_map)
	{
		free(normalized);
		return (0);
	}
	new_map = fill_map_array(config, i, new_map);
	new_map[i] = normalized;
	new_map[i + 1] = NULL;
	free(config->map);
	config->map = new_map;
	config->map_height++;
	return (1);
}

int	start_map_parsing(const char *line, t_config *config)
{
	char	*normalized;

	config->map = malloc(sizeof(char *) * 2);
	if (!config->map)
		return (0);
	normalized = normalize_line(line);
	if (!normalized)
	{
		free(config->map);
		config->map = NULL;
		return (0);
	}
	config->map[0] = normalized;
	config->map[1] = NULL;
	config->map_width = get_line_width(normalized);
	config->map_height = 1;
	return (1);
}
