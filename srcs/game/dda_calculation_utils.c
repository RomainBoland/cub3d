/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_calculation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:14:10 by rboland           #+#    #+#             */
/*   Updated: 2025/07/27 16:14:10 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray_data(t_ray_data *data, t_config *config, float ray_angle)
{
	data->ray_dir_x = cos(ray_angle);
	data->ray_dir_y = sin(ray_angle);
	data->ray_x = config->player.pos_x;
	data->ray_y = config->player.pos_y;
	data->map_x = (int)data->ray_x;
	data->map_y = (int)data->ray_y;
	data->hit = 0;
}

void	calculate_delta_dist(t_ray_data *data)
{
	if (data->ray_dir_x == 0)
		data->delta_dist_x = 1e30;
	else
		data->delta_dist_x = fabs(1 / data->ray_dir_x);
	if (data->ray_dir_y == 0)
		data->delta_dist_y = 1e30;
	else
		data->delta_dist_y = fabs(1 / data->ray_dir_y);
}

void	calculate_step_and_side_dist_x(t_ray_data *data)
{
	if (data->ray_dir_x < 0)
	{
		data->step_x = -1;
		data->side_dist_x = (data->ray_x - data->map_x) * data->delta_dist_x;
	}
	else
	{
		data->step_x = 1;
		data->side_dist_x = (data->map_x + 1.0 - data->ray_x)
			* data->delta_dist_x;
	}
}
