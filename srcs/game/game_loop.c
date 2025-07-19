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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	game_loop(t_config *config)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int f_argb = (255 << 24) | (config->floor_color[0] << 16) | (config->floor_color[1] << 8) | config->floor_color[2];
	int c_argb = (255 << 24) | (config->ceiling_color[0] << 16) | (config->ceiling_color[1] << 8) | config->ceiling_color[2];
	(void)config;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "cub3d");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	int y = 0;
	int x = 0;
	while (y<1080)
	{
		x = 0;
		while (x<1920)
		{
			if (y < 1080/2)
				my_mlx_pixel_put(&img, x, y, c_argb);
			else
				my_mlx_pixel_put(&img, x, y, f_argb);			
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
