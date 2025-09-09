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

#include "cub3d_bonus.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (game->game_state == STATE_MENU)
		return (handle_menu_input(keycode, game));
	else if (game->game_state == STATE_VICTORY)
		return (handle_victory_input(keycode, game));
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
	else if (keycode == UP_ARROW)
		game->key_up = 1;
	else if (keycode == DOWN_ARROW)
		game->key_down = 1;
	else if (keycode == E_KEY)
		game->key_interact = 1;
	else if (keycode == ESC_KEY)
		close_window(game);
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
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
	else if (keycode == UP_ARROW)
		game->key_up = 0;
	else if (keycode == DOWN_ARROW)
		game->key_down = 0;
	else if (keycode == E_KEY)
		game->key_interact = 0;
	return (0);
}

int	close_window(t_game *game)
{
	cleanup_textures(game->mlx, game->config);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	cleanup_config(game->config);
	printf("Game closed successfully!\n");
	exit(0);
	return (0);
}

void	handle_interaction_logic(t_game *game, t_config *config)
{
	static int	last_interact_state = 0;

	if (game->key_interact && !last_interact_state)
	{
		handle_interaction(config);
	}
	last_interact_state = game->key_interact;
	check_door_win_condition(config);
}

void	handle_movement(t_game *game, t_config *config)
{
	float	move[2];
	float	angle[2];

	move[0] = 0;
	move[1] = 0;
	angle[0] = cos(config->player.angle);
	angle[1] = sin(config->player.angle);
	if (game->key_w)
	{
		move[0] += angle[0] * MOVE_SPEED;
		move[1] += angle[1] * MOVE_SPEED;
	}
	if (game->key_s)
	{
		move[0] -= angle[0] * MOVE_SPEED;
		move[1] -= angle[1] * MOVE_SPEED;
	}
	update_game2(game, move, angle, config);
}
