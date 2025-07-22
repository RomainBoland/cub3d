/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:10:58 by rboland           #+#    #+#             */
/*   Updated: 2025/07/22 11:10:58 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Handle key press events
int handle_keypress(int keycode, t_game *game)
{
    if (keycode == W_KEY)
        game->key_w = 1;
    else if (keycode == A_KEY)
        game->key_a = 1;
    else if (keycode == S_KEY)
        game->key_s = 1;
    else if (keycode == D_KEY)
        game->key_d = 1;
    else if (keycode == LEFT_ARROW)
        game->key_left = 1;
    else if (keycode == RIGHT_ARROW)
        game->key_right = 1;
    else if (keycode == ESC_KEY)
        close_window(game);
    
    return (0);
}

int handle_keyrelease(int keycode, t_game *game)
{
    if (keycode == W_KEY)
        game->key_w = 0;
    else if (keycode == A_KEY)
        game->key_a = 0;
    else if (keycode == S_KEY)
        game->key_s = 0;
    else if (keycode == D_KEY)
        game->key_d = 0;
    else if (keycode == LEFT_ARROW)
        game->key_left = 0;
    else if (keycode == RIGHT_ARROW)
        game->key_right = 0;
    
    return (0);
}

// Close window and exit
int close_window(t_game *game)
{
    mlx_destroy_image(game->mlx, game->img.img);
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    free(game->mlx);
    cleanup_config(game->config);
    exit(0);
    return (0);
}

// Update game state based on key presses
void update_game(t_game *game)
{
    t_config *config = game->config;
    
    // Movement calculations
    float move_x = 0, move_y = 0;
    float cos_angle = cos(config->player.angle);
    float sin_angle = sin(config->player.angle);
    
    // Forward/Backward (W/S)
    if (game->key_w)
    {
        move_x += cos_angle * MOVE_SPEED;
        move_y += sin_angle * MOVE_SPEED;
    }
    if (game->key_s)
    {
        move_x -= cos_angle * MOVE_SPEED;
        move_y -= sin_angle * MOVE_SPEED;
    }
    
    // Strafe Left/Right (A/D)
    if (game->key_a)
    {
        move_x += sin_angle * MOVE_SPEED;   // Perpendicular to forward
        move_y -= cos_angle * MOVE_SPEED;
    }
    if (game->key_d)
    {
        move_x -= sin_angle * MOVE_SPEED;
        move_y += cos_angle * MOVE_SPEED;
    }
    
    // Apply movement
    if (move_x != 0 || move_y != 0)
        move_player(config, move_x, move_y);
    
    // Rotation (Arrow keys)
    if (game->key_left)
        rotate_player(config, -ROT_SPEED);
    if (game->key_right)
        rotate_player(config, ROT_SPEED);
}
