/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_door_win_cond.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:22:47 by nsaillez          #+#    #+#             */
/*   Updated: 2025/09/08 10:00:46 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	door_win_cond2(t_interactive *crt, float p_x, float p_y, t_config *cfg)
{
	float	distance;

	while (crt)
	{
		if (crt->type == INTERACTIVE_DOOR
			&& crt->door_state == DOOR_OPENED_UNLOCKED)
		{
			distance = sqrt((p_x - crt->x - 0.5f)
					* (p_x - crt->x - 0.5f)
					+ (p_y - crt->y - 0.5f)
					* (p_y - crt->y - 0.5f));
			if (distance <= 0.7f)
			{
				cfg->game_state.game_won = 1;
				return ;
			}
		}
		crt = crt->next;
	}
}

void	check_door_win_condition(t_config *config)
{
	t_interactive	*current;
	float			player_x;
	float			player_y;

	if (config->game_state.game_won)
		return ;
	player_x = config->player.pos_x;
	player_y = config->player.pos_y;
	current = config->game_state.interactives;
	door_win_cond2(current, player_x, player_y, config);
}
