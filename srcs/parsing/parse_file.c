/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:07:22 by rboland           #+#    #+#             */
/*   Updated: 2025/07/17 00:07:22 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_line_to_map(const char *line, t_config *config)
{
	char	**new_map;
	char	*normalized;
	int		i;
	int		j;

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
	j = 0;
	while (j < i)
	{
		new_map[j] = config->map[j];
		j++;
	}
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
	printf("Map width initialized to %u\n", config->map_width);
	config->map_height = 1;
	return (1);
}

int parse_file2(char *first_line, t_config *config, int fd)
{
    char *line;
    
    if (!start_map_parsing(first_line, config))
        return (0);
    
    line = get_next_line(fd);
    while (line)
    {
        if (!is_empty_line(line))
        {
            if (!add_line_to_map(line, config))
            {
                free(line);
                return (0);
            }
        }
		if ((int)get_line_width(line) > config->map_width)
			config->map_width = (int)get_line_width(line);
        free(line);
        line = get_next_line(fd);
    }
    return (validate_complete_config(config));
}

int parse_file(int fd, t_config *config, t_parse_state *state)
{
    char *line;
    
    line = get_next_line(fd);
    while (line)
    {
        if (is_empty_line(line))
        {
            free(line);
            line = get_next_line(fd);
            continue ;
        }
        if (is_config_line(line))
        {
            if (!parse_config_line(line, config, state))
            {
                free(line);
                cleanup_config(config);
                return (0);
            }
        }
        else if (is_map_line(line))
        {
            if (!all_config_complete(state))
            {
                free(line);
                cleanup_config(config);
                return (print_error("Missing configuration elements"), 0);
            }
            break ;
        }
        else
        {
            free(line);
            return (exit_error("Invalid line format", config));
        }
        free(line);
        line = get_next_line(fd);
    }
    return (parse_file2(line, config, fd));
}

int	file_checker(const char *file_path, int argc, t_config *config)
{
	int				fd;
	t_parse_state	state;

	if (arg_checker(argc, file_path))
		return (0);
	fd = open_map(file_path);
	if (!fd)
		return (0);
	init_parse_state(&state);
	init_config(config);
	parse_file(fd, config, &state);

	return (1);
}
