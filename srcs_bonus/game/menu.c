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

static void	scale_and_draw_pixel(t_game *game, t_texture *texture,
				int x, int y)
{
	int				src_x;
	int				src_y;
	float			scale_x;
	float			scale_y;
	unsigned int	color;

	scale_x = (float)texture->width / WINDOW_WIDTH;
	scale_y = (float)texture->height / WINDOW_HEIGHT;
	src_x = (int)(x * scale_x);
	src_y = (int)(y * scale_y);
	if (src_x >= texture->width)
		src_x = texture->width - 1;
	if (src_y >= texture->height)
		src_y = texture->height - 1;
	color = get_texture_pixel(texture, src_x, src_y);
	my_mlx_pixel_put(&game->img, x, y, color);
}

void	render_scaled_image(t_game *game, t_texture *texture)
{
	int	x;
	int	y;

	if (!texture || !texture->img)
		return ;
	ft_memset(game->img.addr, 0, WINDOW_HEIGHT * game->img.line_length);
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			scale_and_draw_pixel(game, texture, x, y);
			x++;
		}
		y++;
	}
}

void	render_menu_screen(t_game *game)
{
	render_scaled_image(game, &game->config->tex.menu_screen);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	render_victory_screen(t_game *game)
{
	render_scaled_image(game, &game->config->tex.victory_screen);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
