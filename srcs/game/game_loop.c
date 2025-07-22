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

#include "cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return;
    
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int game_loop_hook(t_game *game)
{
    // Update game state based on key presses
    update_game(game);
    
    // Render the frame
    render_raycast(game->config, &game->img);
    
    // Display the frame
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    
    return (0);
}

void game_loop(t_config *config)
{
    t_game game;
    
    // Initialize game structure
    game.config = config;
    game.mlx = mlx_init();
    if (!game.mlx)
    {
        print_error("Failed to initialize MLX");
        return;
    }
    
    // Load all textures BEFORE creating the window
    if (!load_all_textures(game.mlx, config))
    {
        print_error("Failed to load textures");
        mlx_destroy_display(game.mlx);
        free(game.mlx);
        return;
    }
    
    game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D - Textured Raycaster");
    if (!game.win)
    {
        cleanup_textures(game.mlx, config);
        mlx_destroy_display(game.mlx);
        free(game.mlx);
        print_error("Failed to create window");
        return;
    }
    
    game.img.img = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!game.img.img)
    {
        cleanup_textures(game.mlx, config);
        mlx_destroy_window(game.mlx, game.win);
        mlx_destroy_display(game.mlx);
        free(game.mlx);
        print_error("Failed to create image");
        return;
    }
    
    game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, 
                                      &game.img.line_length, &game.img.endian);
    
    // Initialize key states
    game.key_w = 0;
    game.key_a = 0;
    game.key_s = 0;
    game.key_d = 0;
    game.key_left = 0;
    game.key_right = 0;

    // Set up event hooks
    mlx_hook(game.win, 17, 1L<<17, close_window, &game);          // Window close (X button)
    mlx_hook(game.win, 2, 1L<<0, handle_keypress, &game);         // Key press
    mlx_hook(game.win, 3, 1L<<1, handle_keyrelease, &game);       // Key release
    mlx_loop_hook(game.mlx, game_loop_hook, &game);               // Main game loop
    
    // Initial render
    render_raycast(config, &game.img);
    mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
    
    printf("🎮 Cub3D - Textured Raycaster Controls:\n");
    printf("   WASD: Move player\n");
    printf("   Arrow Keys: Rotate view\n");
    printf("   ESC: Exit\n\n");
    printf("Player starting at (%.2f, %.2f) facing %.2f radians\n", 
           config->player.pos_x, config->player.pos_y, config->player.angle);
    
    // Start the game loop
    mlx_loop(game.mlx);
}
