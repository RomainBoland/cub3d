/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:31:05 by rboland           #+#    #+#             */
/*   Updated: 2025/07/22 13:31:05 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_texture(void *mlx, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		print_error("Failed to load texture");
		return (0);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
	{
		mlx_destroy_image(mlx, texture->img);
		print_error("Failed to get texture address");
		return (0);
	}
	return (1);
}

int	load_all_textures(void *mlx, t_config *config)
{
	if (!load_texture(mlx, &config->tex.north, config->north_texture))
		return (0);
	if (!load_texture(mlx, &config->tex.south, config->south_texture))
		return (0);
	if (!load_texture(mlx, &config->tex.west, config->west_texture))
		return (0);
	if (!load_texture(mlx, &config->tex.east, config->east_texture))
		return (0);
	return (1);
}

void	cleanup_textures(void *mlx, t_config *config)
{
	if (config->tex.north.img)
		mlx_destroy_image(mlx, config->tex.north.img);
	if (config->tex.south.img)
		mlx_destroy_image(mlx, config->tex.south.img);
	if (config->tex.west.img)
		mlx_destroy_image(mlx, config->tex.west.img);
	if (config->tex.east.img)
		mlx_destroy_image(mlx, config->tex.east.img);
	config->tex.north.img = NULL;
	config->tex.south.img = NULL;
	config->tex.west.img = NULL;
	config->tex.east.img = NULL;
}

unsigned int	get_texture_pixel(t_texture *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x000000);
	pixel = (texture->addr + (y * texture->line_length
				+ x * (texture->bits_per_pixel / 8)));
	return (*(unsigned int *)pixel);
}
