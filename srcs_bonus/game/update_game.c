/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:14:08 by nsaillez          #+#    #+#             */
/*   Updated: 2025/09/08 10:21:35 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_game2(t_game *game, float *move, float *angle, t_config *config)
{
	if (game->key_a)
	{
		move[0] += angle[1] * MOVE_SPEED;
		move[1] -= angle[0] * MOVE_SPEED;
	}
	if (game->key_d)
	{
		move[0] -= angle[1] * MOVE_SPEED;
		move[1] += angle[0] * MOVE_SPEED;
	}
	if (move[0] != 0 || move[1] != 0)
		move_player(config, move[0], move[1]);
	if (game->key_left)
		rotate_player(config, -ROT_SPEED);
	if (game->key_right)
		rotate_player(config, ROT_SPEED);
	if (game->key_up)
		change_pitch(config, PITCH_SPEED);
	if (game->key_down)
		change_pitch(config, -PITCH_SPEED);
}

void	update_game(t_game *game)
{
	t_config	*config;

	config = game->config;
	if (game->game_state != STATE_PLAYING)
		return ;
	if (config->game_state.game_won && game->game_state == STATE_PLAYING)
	{
		game->game_state = STATE_VICTORY;
		return ;
	}
	handle_movement(game, config);
	handle_interaction_logic(game, config);
}
