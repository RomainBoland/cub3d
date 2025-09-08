/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_menu_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:25:58 by nsaillez          #+#    #+#             */
/*   Updated: 2025/09/08 09:26:06 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	handle_menu_input(int keycode, t_game *game)
{
	(void)keycode;
	if (keycode == ESC_KEY)
	{
		close_window(game);
		return (0);
	}
	game->game_state = STATE_PLAYING;
	printf("🎮 Game started! Good luck!\n");
	return (0);
}

int	handle_victory_input(int keycode, t_game *game)
{
	(void)keycode;
	if (keycode == ESC_KEY)
	{
		close_window(game);
		return (0);
	}
	printf("🎉 Thanks for playing!\n");
	close_window(game);
	return (0);
}
