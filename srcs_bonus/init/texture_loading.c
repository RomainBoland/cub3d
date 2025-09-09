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

static int	load_lever_textures(void *mlx, t_config *config)
{
	if (config->lever_off_north_texture
		&& !load_texture(mlx, &config->tex.lever_off_north,
			config->lever_off_north_texture))
		return (0);
	if (config->lever_off_south_texture
		&& !load_texture(mlx, &config->tex.lever_off_south,
			config->lever_off_south_texture))
		return (0);
	if (config->lever_off_base_texture
		&& !load_texture(mlx, &config->tex.lever_off_base,
			config->lever_off_base_texture))
		return (0);
	return (1);
}

static int	load_lever_textures2(void *mlx, t_config *config)
{
	if (config->lever_on_north_texture
		&& !load_texture(mlx, &config->tex.lever_on_north,
			config->lever_on_north_texture))
		return (0);
	if (config->lever_on_south_texture
		&& !load_texture(mlx, &config->tex.lever_on_south,
			config->lever_on_south_texture))
		return (0);
	if (config->lever_on_base_texture
		&& !load_texture(mlx, &config->tex.lever_on_base,
			config->lever_on_base_texture))
		return (0);
	return (1);
}

static int	load_menu_textures(void *mlx, t_config *config)
{
	if (!load_texture(mlx, &config->tex.menu_screen,
			"textures/door_red.xpm"))
	{
		printf("Warning: Could not load menu screen, using fallback\n");
	}
	if (!load_texture(mlx, &config->tex.victory_screen,
			"textures/door_red.xpm"))
	{
		printf("Warning: Could not load victory screen, using fallback\n");
	}
	return (1);
}

int	load_all_textures(void *mlx, t_config *config)
{
	if (!load_basic_textures(mlx, config))
		return (0);
	if (!load_door_textures(mlx, config))
		return (0);
	if (!load_lever_textures(mlx, config))
		return (0);
	if (!load_lever_textures2(mlx, config))
		return (0);
	load_menu_textures(mlx, config);
	return (1);
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
