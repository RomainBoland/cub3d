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

int	parse_file(const char *file_path)
{
	int fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	return (0);
}

int str_ends_with(const char *str, const char *suffix)
{
	size_t str_len;
	size_t suffix_len;

	str_len = ft_strlen(str);
	suffix_len = ft_strlen(suffix);
	if (suffix_len > str_len)
		return 0;
	return (ft_strncmp(str + str_len - suffix_len, suffix, 4) == 0);
}

int arg_checker(int argc, const char *file_path)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Usage: ./cub3d <path_to_map_file.cub>\n", 2);
		return (1);
	}
	if (!str_ends_with(file_path, ".cub"))
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("File must have a .cub extension\n", 2);
		return (1);
	}
	return (0);
}

int file_checker(const char *file_path, int argc)
{
	if (arg_checker(argc, file_path))
		return (1);
	ft_putstr_fd("Game started with map: ", 1);
	ft_putstr_fd(file_path, 1);
	ft_putchar_fd('\n', 1);

	return (0);
}
