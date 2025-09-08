/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:34:48 by nsaillez          #+#    #+#             */
/*   Updated: 2025/09/08 10:36:31 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_valid_texture2(void *mlx, t_config *config, int valid)
{
	int	is_valid;

	is_valid = valid;
	if (!validate_texture_path(mlx, config->floor_texture))
	{
		print_error("Invalid Floor texture path");
		is_valid = 0;
	}
	if (!validate_texture_path(mlx, config->ceiling_texture))
	{
		print_error("Invalid Ceiling texture path");
		is_valid = 0;
	}
	return (is_valid);
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
	return (is_valid_texture2(mlx, config, valid));
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
	if (valid)
		valid = validate_interactive_textures(mlx, config);
	mlx_destroy_display(mlx);
	free(mlx);
	return (valid);
}
