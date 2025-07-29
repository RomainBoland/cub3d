/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:46:37 by nsaillez          #+#    #+#             */
/*   Updated: 2025/07/29 12:04:39 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_mini_map(t_game *game)
{
	int r = 50;
	int x;
	int y;
	//t_player player = game->config->player;
	//int is_inside;
	
	y = 0;
	while (y < 100)
	{
		x = 0;
		while (x < 100)
		{
			if ((x-50) * (x-50) + (y-50) * (y-50) <= r*r)
				my_mlx_pixel_put(&game->img, x+10, y+10, 0xff00ff);
			if (((x-50) * (x-50) + (y-50) * (y-50)) <= r*r-200)
				my_mlx_pixel_put(&game->img, x+10, y+10, 0x000000);
			x++;
		}
		y++;
	}
	//printf("Player x: %f, y: %f\n", player.pos_x, player.pos_y);
}