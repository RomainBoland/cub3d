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

int load_all_textures(void *mlx, t_config *config)
{
    printf("DEBUG: Starting texture loading...\n");
    
    // Load basic wall/floor/ceiling textures
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
    
    printf("DEBUG: Basic textures loaded. Loading interactive textures...\n");
    
    // Load interactive textures (only if paths are provided)
    if (config->door_locked_texture && 
        !load_texture(mlx, &config->tex.door_locked, config->door_locked_texture))
        return (0);
    if (config->door_unlocked_texture && 
        !load_texture(mlx, &config->tex.door_unlocked, config->door_unlocked_texture))
        return (0);
    if (config->door_open_texture && 
        !load_texture(mlx, &config->tex.door_open, config->door_open_texture))
        return (0);
    if (config->lever_off_north_texture && 
        !load_texture(mlx, &config->tex.lever_off_north, config->lever_off_north_texture))
        return (0);
    if (config->lever_off_south_texture && 
        !load_texture(mlx, &config->tex.lever_off_south, config->lever_off_south_texture))
        return (0);
    if (config->lever_off_base_texture && 
        !load_texture(mlx, &config->tex.lever_off_base, config->lever_off_base_texture))
        return (0);
    if (config->lever_on_north_texture && 
        !load_texture(mlx, &config->tex.lever_on_north, config->lever_on_north_texture))
        return (0);
    if (config->lever_on_south_texture && 
        !load_texture(mlx, &config->tex.lever_on_south, config->lever_on_south_texture))
        return (0);
    if (config->lever_on_base_texture && 
        !load_texture(mlx, &config->tex.lever_on_base, config->lever_on_base_texture))
        return (0);
    
    printf("DEBUG: All textures loaded successfully!\n");
    return (1);
}

void cleanup_textures(void *mlx, t_config *config)
{
    // Cleanup basic textures
    if (config->tex.north.img)
        mlx_destroy_image(mlx, config->tex.north.img);
    if (config->tex.south.img)
        mlx_destroy_image(mlx, config->tex.south.img);
    if (config->tex.west.img)
        mlx_destroy_image(mlx, config->tex.west.img);
    if (config->tex.east.img)
        mlx_destroy_image(mlx, config->tex.east.img);
    if (config->tex.floor.img)
        mlx_destroy_image(mlx, config->tex.floor.img);
    if (config->tex.ceiling.img)
        mlx_destroy_image(mlx, config->tex.ceiling.img);
    if (config->tex.door_locked.img)
        mlx_destroy_image(mlx, config->tex.door_locked.img);
    if (config->tex.door_unlocked.img)
        mlx_destroy_image(mlx, config->tex.door_unlocked.img);
    if (config->tex.door_open.img)
        mlx_destroy_image(mlx, config->tex.door_open.img);
    if (config->tex.lever_off_north.img)
        mlx_destroy_image(mlx, config->tex.lever_off_north.img);
    if (config->tex.lever_off_south.img)
        mlx_destroy_image(mlx, config->tex.lever_off_south.img);
    if (config->tex.lever_off_base.img)
        mlx_destroy_image(mlx, config->tex.lever_off_base.img);
    if (config->tex.lever_on_north.img)
        mlx_destroy_image(mlx, config->tex.lever_on_north.img);
    if (config->tex.lever_on_south.img)
        mlx_destroy_image(mlx, config->tex.lever_on_south.img);
    if (config->tex.lever_on_base.img)
        mlx_destroy_image(mlx, config->tex.lever_on_base.img);
    
    // Reset all texture pointers
    config->tex.north.img = NULL;
    config->tex.south.img = NULL;
    config->tex.west.img = NULL;
    config->tex.east.img = NULL;
    config->tex.floor.img = NULL;
    config->tex.ceiling.img = NULL;
    config->tex.door_locked.img = NULL;
    config->tex.door_unlocked.img = NULL;
    config->tex.door_open.img = NULL;
    config->tex.lever_off_north.img = NULL;
    config->tex.lever_off_south.img = NULL;
    config->tex.lever_off_base.img = NULL;
    config->tex.lever_on_north.img = NULL;
    config->tex.lever_on_south.img = NULL;
    config->tex.lever_on_base.img = NULL;
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
