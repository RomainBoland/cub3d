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

#include "cub3d_bonus.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int game_loop_hook(t_game *game)
{
    // Handle different game states
    if (game->game_state == STATE_MENU)
    {
        render_menu_screen(game);
    }
    else if (game->game_state == STATE_VICTORY)
    {
        render_victory_screen(game);
    }
    else // STATE_PLAYING
    {
        update_game(game);
        ft_memset(game->img.addr, 0, WINDOW_HEIGHT * game->img.line_length);
        render_raycast(game->config, &game->img);
        update_mini_map(game);
        mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    }
    
    return (0);
}

void	print_game_info(t_config *config)
{
	(void)config;
	printf("🎮 Cub3D - Textured Raycaster Controls:\n");
	printf("   WASD:	Move player\n");
	printf("   E:		Interact\n");
	printf("   Arrow Keys:	Rotate view\n");
	printf("   ESC:		Exit\n\n");
}
