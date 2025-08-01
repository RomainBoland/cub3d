/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:21:09 by rboland           #+#    #+#             */
/*   Updated: 2025/07/27 15:21:09 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	game_loop_hook(t_game *game)
{
	update_game(game);
	render_raycast(game->config, &game->img);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

void	print_game_info(t_config *config)
{
	printf("🎮 Cub3D - Textured Raycaster Controls:\n");
	printf("   WASD: Move player\n");
	printf("   Arrow Keys: Rotate view\n");
	printf("   ESC: Exit\n\n");
	printf("Player starting at (%.2f, %.2f) facing %.2f radians\n",
		config->player.pos_x, config->player.pos_y, config->player.angle);
}
