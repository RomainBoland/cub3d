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

static int validate_interactive_textures(void *mlx, t_config *config)
{
    int valid = 1;
    
    // Only validate interactive textures if they're provided
    if (config->door_locked_texture && 
        !validate_texture_path(mlx, config->door_locked_texture))
    {
        print_error("Invalid Door Locked texture path");
        valid = 0;
    }
    if (config->door_unlocked_texture && 
        !validate_texture_path(mlx, config->door_unlocked_texture))
    {
        print_error("Invalid Door Unlocked texture path");
        valid = 0;
    }
    if (config->door_open_texture && 
        !validate_texture_path(mlx, config->door_open_texture))
    {
        print_error("Invalid Door Open texture path");
        valid = 0;
    }
    if (config->lever_off_north_texture && 
        !validate_texture_path(mlx, config->lever_off_north_texture))
    {
        print_error("Invalid Lever Off North texture path");
        valid = 0;
    }
    if (config->lever_off_south_texture && 
        !validate_texture_path(mlx, config->lever_off_south_texture))
    {
        print_error("Invalid Lever Off South texture path");
        valid = 0;
    }
    if (config->lever_off_base_texture && 
        !validate_texture_path(mlx, config->lever_off_base_texture))
    {
        print_error("Invalid Lever Off Base texture path");
        valid = 0;
    }
    if (config->lever_on_north_texture && 
        !validate_texture_path(mlx, config->lever_on_north_texture))
    {
        print_error("Invalid Lever On North texture path");
        valid = 0;
    }
    if (config->lever_on_south_texture && 
        !validate_texture_path(mlx, config->lever_on_south_texture))
    {
        print_error("Invalid Lever On South texture path");
        valid = 0;
    }
    if (config->lever_on_base_texture && 
        !validate_texture_path(mlx, config->lever_on_base_texture))
    {
        print_error("Invalid Lever On Base texture path");
        valid = 0;
    }
    
    return (valid);
}

static int	is_valid_texture2(void *mlx, t_config *config,
	int valid)
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
