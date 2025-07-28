/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:26:13 by rboland           #+#    #+#             */
/*   Updated: 2025/07/19 17:26:13 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	init_mlx_resources(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		print_error("Failed to initialize MLX");
		return (0);
	}
	if (!load_all_textures(game->mlx, game->config))
	{
		print_error("Failed to load textures");
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (0);
	}
	return (1);
}

static int	create_window_and_image(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cub3D - Textured Raycaster");
	if (!game->win)
	{
		cleanup_textures(game->mlx, game->config);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		print_error("Failed to create window");
		return (0);
	}
	game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img.img)
	{
		cleanup_textures(game->mlx, game->config);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		print_error("Failed to create image");
		return (0);
	}
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	return (1);
}

static void	init_key_states(t_game *game)
{
	game->key_w = 0;
	game->key_a = 0;
	game->key_s = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;
	game->key_down = 0;
	game->key_up = 0;
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, handle_keyrelease, game);
	mlx_loop_hook(game->mlx, game_loop_hook, game);
}

void	game_loop(t_config *config)
{
	t_game	game;

	game.config = config;
	if (!init_mlx_resources(&game))
		return ;
	if (!create_window_and_image(&game))
		return ;
	init_key_states(&game);
	setup_hooks(&game);
	print_game_info(config);
	mlx_loop(game.mlx);
}
