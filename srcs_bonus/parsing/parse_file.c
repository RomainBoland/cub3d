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

#include "cub3d_bonus.h"

static int	parse_remaining_lines(char *first_line, t_config *config, int fd)
{
	char	*line;

	if (!start_map_parsing(first_line, config))
		return (free(first_line), 0);
	free(first_line);
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

static int	process_config_line(char *line, t_config *config,
	t_parse_state *state)
{
	if (!parse_config_line(line, config, state))
	{
		free(line);
		cleanup_config(config);
		return (0);
	}
	return (1);
}

static int	handle_map_start(char *line, t_config *config,
	t_parse_state *state, int fd)
{
	if (!all_config_complete(state))
	{
		free(line);
		cleanup_config(config);
		return (print_error("Missing configuration elements"), 0);
	}
	return (parse_remaining_lines(line, config, fd));
}

int	parse_file(int fd, t_config *config, t_parse_state *state)
{
	char	*line;

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
			if (!process_config_line(line, config, state))
				return (0);
		}
		else if (is_map_line(line))
			return (handle_map_start(line, config, state, fd));
		else
			return (free(line), exit_error("Invalid line format", config));
		free(line);
		line = get_next_line(fd);
	}
	return (parse_remaining_lines(line, config, fd));
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
	if (!parse_file(fd, config, &state))
	{
		close(fd);
		return (0);
	}
	return (1);
}
