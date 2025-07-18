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

int add_line_to_map(const char *line, t_config *config)
{
	char **new_map;
	int i;
	int j;

	printf("Adding line to map: %s\n", line);
	i = 0;
	while (config->map[i])
		i++;
	printf("Current map height: %d\n", i);
	new_map = malloc(sizeof(char *) * (i + 2));
	if (!new_map)
		return (0);
	j = 0;
	while (j < i)
	{
		new_map[j] = config->map[j];
		j++;
	}
	new_map[i] = ft_strdup(line);
	new_map[i + 1] = NULL;
	free(config->map);
	config->map = new_map;
	config->map_height++;
	return (1);
}

int start_map_parsing(const char *line, t_config *config)
{
    config->map = malloc(sizeof(char *) * 2); // Space for 1 line + NULL
    if (!config->map)
        return (0);
    
    config->map[0] = ft_strdup(line);
    if (!config->map[0])
    {
        free(config->map);
        config->map = NULL;
        return (0);
    }
    
    config->map[1] = NULL;
    config->map_width = ft_strlen(line);
    config->map_height = 1;
    return (1);
}

int parse_file2(char *line, t_config *config, int fd)
{
	start_map_parsing(line, config);
    while (line)
    {
		printf("Processing map line: %s\n", line);
        if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
            continue ;
		}
        add_line_to_map(line, config);
		free(line);
		line = get_next_line(fd);
		printf("Next line...\n");
    }
    return (validate_complete_config(config));
}

int parse_file(int fd, t_config *config, t_parse_state *state)
{
    char *line;
    
    line = get_next_line(fd);
    while (line && !state->all_config_found)
    {
		printf("Parsing line: %s", line);
        if (is_empty_line(line))
        {
			printf("Skipping empty line\n");
            free(line);
            line = get_next_line(fd);
            continue;
        }
        if (is_config_line(line))
        {
			printf("Parsing config line: %s", line);
            if (!parse_config_line(line, config, state))
            {
				printf("Error parsing config line: %s", line);
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
			printf("Initializing map with line: %s", line);
            free(line);
            break ;
        }
        else
        {
            free(line);
            return (exit_error("Invalid line format", config));
        }
        free(line);
        line = get_next_line(fd);
		printf("Line processed successfuly...\n");
    }
	printf("End of file reached or all config found.\n");
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
	printf("Initializing parse state...\n");
	init_parse_state(&state);
	printf("Initializing configuration...\n");
	init_config(config);
	printf("Parsing file: %s\n", file_path);
	parse_file(fd, config, &state);

	return (1);
}
