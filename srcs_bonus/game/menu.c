/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:10:22 by rboland           #+#    #+#             */
/*   Updated: 2025/08/20 10:10:22 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// Render an image scaled to fit the window
void render_scaled_image(t_game *game, t_texture *texture)
{
    int x, y;
    int src_x, src_y;
    float scale_x, scale_y;
    unsigned int color;
    
    if (!texture || !texture->img)
        return;
    
    // Calculate scaling factors
    scale_x = (float)texture->width / WINDOW_WIDTH;
    scale_y = (float)texture->height / WINDOW_HEIGHT;
    
    // Clear the screen first
    ft_memset(game->img.addr, 0, WINDOW_HEIGHT * game->img.line_length);
    
    // Scale and draw the image
    for (y = 0; y < WINDOW_HEIGHT; y++)
    {
        for (x = 0; x < WINDOW_WIDTH; x++)
        {
            src_x = (int)(x * scale_x);
            src_y = (int)(y * scale_y);
            
            // Ensure we don't go out of bounds
            if (src_x >= texture->width)
                src_x = texture->width - 1;
            if (src_y >= texture->height)
                src_y = texture->height - 1;
            
            color = get_texture_pixel(texture, src_x, src_y);
            my_mlx_pixel_put(&game->img, x, y, color);
        }
    }
}

void render_menu_screen(t_game *game)
{
    render_scaled_image(game, &game->config->tex.menu_screen);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void render_victory_screen(t_game *game)
{
    render_scaled_image(game, &game->config->tex.victory_screen);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

int handle_menu_input(int keycode, t_game *game)
{
    (void)keycode; // Any key starts the game
    
    if (keycode == ESC_KEY)
    {
        close_window(game);
        return (0);
    }
    
    // Start the game
    game->game_state = STATE_PLAYING;
    printf("🎮 Game started! Good luck!\n");
    return (0);
}

int handle_victory_input(int keycode, t_game *game)
{
    (void)keycode; // Any key exits or restarts
    
    if (keycode == ESC_KEY)
    {
        close_window(game);
        return (0);
    }
    
    // You can either restart the game or close it
    // For now, let's close the game
    printf("🎉 Thanks for playing!\n");
    close_window(game);
    return (0);
}
