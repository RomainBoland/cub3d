/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:36:58 by rboland           #+#    #+#             */
/*   Updated: 2025/07/21 15:36:58 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	validate_texture_path(void *mlx, char *path)
{
	void	*img;
	int		width;
	int		height;

	if (!path || !*path)
		return (0);
	img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!img)
		return (0);
	mlx_destroy_image(mlx, img);
	return (1);
}

static int	validate_door_textures(void *mlx, t_config *config)
{
	int	valid;

	valid = 1;
	if (config->door_locked_texture
		&& !validate_texture_path(mlx, config->door_locked_texture))
	{
		print_error("Invalid Door Locked texture path");
		valid = 0;
	}
	if (config->door_unlocked_texture
		&& !validate_texture_path(mlx, config->door_unlocked_texture))
	{
		print_error("Invalid Door Unlocked texture path");
		valid = 0;
	}
	if (config->door_open_texture
		&& !validate_texture_path(mlx, config->door_open_texture))
	{
		print_error("Invalid Door Open texture path");
		valid = 0;
	}
	return (valid);
}

static int	validate_lever_off_textures(void *mlx, t_config *config)
{
	int	valid;

	valid = 1;
	if (config->lever_off_north_texture
		&& !validate_texture_path(mlx, config->lever_off_north_texture))
	{
		print_error("Invalid Lever Off North texture path");
		valid = 0;
	}
	if (config->lever_off_south_texture
		&& !validate_texture_path(mlx, config->lever_off_south_texture))
	{
		print_error("Invalid Lever Off South texture path");
		valid = 0;
	}
	if (config->lever_off_base_texture
		&& !validate_texture_path(mlx, config->lever_off_base_texture))
	{
		print_error("Invalid Lever Off Base texture path");
		valid = 0;
	}
	return (valid);
}

static int	validate_lever_on_textures(void *mlx, t_config *config)
{
	int	valid;

	valid = 1;
	if (config->lever_on_north_texture
		&& !validate_texture_path(mlx, config->lever_on_north_texture))
	{
		print_error("Invalid Lever On North texture path");
		valid = 0;
	}
	if (config->lever_on_south_texture
		&& !validate_texture_path(mlx, config->lever_on_south_texture))
	{
		print_error("Invalid Lever On South texture path");
		valid = 0;
	}
	if (config->lever_on_base_texture
		&& !validate_texture_path(mlx, config->lever_on_base_texture))
	{
		print_error("Invalid Lever On Base texture path");
		valid = 0;
	}
	return (valid);
}

int	validate_interactive_textures(void *mlx, t_config *config)
{
	int	valid;

	valid = 1;
	if (!validate_door_textures(mlx, config))
		valid = 0;
	if (!validate_lever_off_textures(mlx, config))
		valid = 0;
	if (!validate_lever_on_textures(mlx, config))
		valid = 0;
	return (valid);
}
