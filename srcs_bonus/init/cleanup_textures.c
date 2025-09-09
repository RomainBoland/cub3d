/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:26:07 by nsaillez          #+#    #+#             */
/*   Updated: 2025/09/09 20:25:50 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cleanup_basic_textures(void *mlx, t_config *config)
{
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
	config->tex.north.img = NULL;
	config->tex.south.img = NULL;
	config->tex.west.img = NULL;
	config->tex.east.img = NULL;
	config->tex.floor.img = NULL;
}

void	cleanup_door_textures(void *mlx, t_config *config)
{
	if (config->tex.ceiling.img)
		mlx_destroy_image(mlx, config->tex.ceiling.img);
	if (config->tex.door_locked.img)
		mlx_destroy_image(mlx, config->tex.door_locked.img);
	if (config->tex.door_unlocked.img)
		mlx_destroy_image(mlx, config->tex.door_unlocked.img);
	if (config->tex.door_open.img)
		mlx_destroy_image(mlx, config->tex.door_open.img);
	config->tex.ceiling.img = NULL;
	config->tex.door_locked.img = NULL;
	config->tex.door_unlocked.img = NULL;
	config->tex.door_open.img = NULL;
}

void	cleanup_lever_textures(void *mlx, t_config *config)
{
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
	config->tex.lever_off_north.img = NULL;
	config->tex.lever_off_south.img = NULL;
	config->tex.lever_off_base.img = NULL;
	config->tex.lever_on_north.img = NULL;
	config->tex.lever_on_south.img = NULL;
}

void	cleanup_menu_textures(void *mlx, t_config *config)
{
	if (config->tex.lever_on_base.img)
		mlx_destroy_image(mlx, config->tex.lever_on_base.img);
	if (config->tex.menu_screen.img)
		mlx_destroy_image(mlx, config->tex.menu_screen.img);
	if (config->tex.victory_screen.img)
		mlx_destroy_image(mlx, config->tex.victory_screen.img);
	config->tex.lever_on_base.img = NULL;
	config->tex.menu_screen.img = NULL;
	config->tex.victory_screen.img = NULL;
}

void	cleanup_textures(void *mlx, t_config *config)
{
	cleanup_basic_textures(mlx, config);
	cleanup_door_textures(mlx, config);
	cleanup_lever_textures(mlx, config);
	cleanup_menu_textures(mlx, config);
}
