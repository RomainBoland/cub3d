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

int	open_map(const char *file_path)
{
	int fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		exit_error("Failed to open map file");
		return (1);
	}
	return (fd);
}

int	str_ends_with(const char *str, const char *suffix)
{
	size_t str_len;
	size_t suffix_len;

	str_len = ft_strlen(str);
	suffix_len = ft_strlen(suffix);
	if (suffix_len > str_len)
		return 0;
	return (ft_strncmp(str + str_len - suffix_len, suffix, 4) == 0);
}

int	arg_checker(int argc, const char *file_path)
{
	if (argc != 2)
	{
		exit_error("Usage: ./cub3d <map_file.cub>");
		return (1);
	}
	if (!str_ends_with(file_path, ".cub"))
	{
		exit_error("File must have a .cub extension");
		return (1);
	}
	return (0);
}

int	parse_file(int fd)
{
	char *line;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strlen(line) == 0 || line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		printf("Line: %s", line);
		// process_line(line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\n");
	if (line)
		free(line);
	close(fd);
	return (0);
}

int	file_checker(const char *file_path, int argc)
{
	int	fd;

	if (arg_checker(argc, file_path))
		return (1);
	fd = open_map(file_path);
	if (!fd)
		return (1);
	parse_file(fd);


	// ft_putstr_fd("Game started with map: ", 1);
	// ft_putstr_fd(file_path, 1);
	// ft_putchar_fd('\n', 1);

	return (0);
}
