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

#include "cub3d.h"

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

static int	is_valid_texture(void *mlx, t_config *config)
{
	int	valid;

	valid = 1;
	if (!validate_texture_path(mlx, config->north_texture))
	{
		print_error("Invalid North texture path");
		valid = 0;
	}
	if (!validate_texture_path(mlx, config->south_texture))
	{
		print_error("Invalid South texture path");
		valid = 0;
	}
	if (!validate_texture_path(mlx, config->west_texture))
	{
		print_error("Invalid West texture path");
		valid = 0;
	}
	if (!validate_texture_path(mlx, config->east_texture))
	{
		print_error("Invalid East texture path");
		valid = 0;
	}
	return (valid);
}

int	validate_all_textures(t_config *config)
{
	void	*mlx;
	int		valid;

	valid = 1;
	mlx = mlx_init();
	if (!mlx)
		return (print_error("Failed to initialize MLX"), 0);
	valid = is_valid_texture(mlx, config);
	mlx_destroy_display(mlx);
	free(mlx);
	return (valid);
}
