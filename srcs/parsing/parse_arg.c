/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:22:22 by rboland           #+#    #+#             */
/*   Updated: 2025/07/17 16:22:22 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_map(const char *file_path)
{
	int fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		print_error("Failed to open map file");
		return (0);
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
		print_error("Usage: ./cub3d <map_file.cub>");
		return (1);
	}
	if (!str_ends_with(file_path, ".cub"))
	{
		print_error("File must have a .cub extension");
		return (1);
	}
	return (0);
}
