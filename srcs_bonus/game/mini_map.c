/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:46:37 by nsaillez          #+#    #+#             */
/*   Updated: 2025/08/01 13:35:17 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void draw_square(t_game *game, int sq_x, int sq_y)
{
	int x;
	int y;
	int size = 10;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			my_mlx_pixel_put(&game->img, sq_x+x+5, sq_y+y+5, 0xff0000);
			x++;
		}
		y++;
	}
}
int is_inside_circle(int x, int y, int r)
{
	if (((x) * (x)) + ((y) * (y)) <= r * r)
		return (1);
	else
		return (0);
}

void	update_mini_map(t_game *game)
{
	int r = 50;
	int size = r * 2;
	int x;
	int y;
	t_player player = game->config->player;

	//printf("angle :%f\n",player.angle);

	float angle = (player.angle * (180/PI))-(FOV_HALF_TAN* (180/PI)/2);
	if (angle >= 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	float startAngle;
	float endAngle;

	//printf("Angle :%f, start: %f, end: %f\n",angle, startAngle, endAngle);

	//int is_inside;

	float Angle;
	y = 0;
	x = 0;
	Angle = atan2(y - r,x - r) * (180/PI);
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			startAngle = angle;
			endAngle = FOV_HALF_TAN * (180/PI) + startAngle;
			if (endAngle >= 360)
				endAngle -= 360;
			Angle = atan2(y - r,x - r) * (180/PI);
			if (Angle < 0)
				Angle += 360;
			if (is_inside_circle(x-r, y-r, r))
			{
				my_mlx_pixel_put(&game->img, x+10, y+10, 0x000000);
				if (startAngle < endAngle)
				{
					if (Angle>=startAngle && Angle<=endAngle)
						my_mlx_pixel_put(&game->img, x+10, y+10, 0xaa0000ff);
				}
				else
				{
					if((Angle >= startAngle || Angle <= endAngle))
						my_mlx_pixel_put(&game->img, x+10, y+10, 0xaa0000ff);
				}
				if (((x-r) * (x-r) + (y-r) * (y-r)) >= r*r-500)
					my_mlx_pixel_put(&game->img, x+10, y+10, 0xff00ff);
				if (is_inside_circle(x-r, y-r, 10))
					my_mlx_pixel_put(&game->img, x+10, y+10, 0x00ff00);
			}
			// Player (green)
			x++;
			//printf("player: %d %d\n", (int)player.pos_x,(int)player.pos_y);
			// if ((x-r) * (x-r) + (y-r) * (y-r) <= r*r && game->config->map[(int)player.pos_y][(int)player.pos_x] == '0')
			// 	draw_square(game, r, r);
		}
		//printf("Angle :%f, start: %f, end: %f\n",Angle, startAngle, endAngle);
		y++;
	}
	//printf("Player x: %f, y: %f\n", player.pos_x, player.pos_y);
}