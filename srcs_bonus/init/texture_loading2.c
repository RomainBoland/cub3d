/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:28:59 by nsaillez          #+#    #+#             */
/*   Updated: 2025/09/08 10:29:37 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	load_texture(void *mlx, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		print_error(" texture");
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

int	load_basic_textures(void *mlx, t_config *config)
{
	if (!load_texture(mlx, &config->tex.north, config->north_texture))
		return (0);
	if (!load_texture(mlx, &config->tex.south, config->south_texture))
		return (0);
	if (!load_texture(mlx, &config->tex.west, config->west_texture))
		return (0);
	if (!load_texture(mlx, &config->tex.east, config->east_texture))
		return (0);
	if (!load_texture(mlx, &config->tex.floor, config->floor_texture))
		return (0);
	if (!load_texture(mlx, &config->tex.ceiling, config->ceiling_texture))
		return (0);
	return (1);
}

int	load_door_textures(void *mlx, t_config *config)
{
	if (config->door_locked_texture
		&& !load_texture(mlx, &config->tex.door_locked,
			config->door_locked_texture))
		return (0);
	if (config->door_unlocked_texture
		&& !load_texture(mlx, &config->tex.door_unlocked,
			config->door_unlocked_texture))
		return (0);
	if (config->door_open_texture
		&& !load_texture(mlx, &config->tex.door_open,
			config->door_open_texture))
		return (0);
	return (1);
}
