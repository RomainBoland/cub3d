/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:56:30 by rboland           #+#    #+#             */
/*   Updated: 2025/07/27 15:56:30 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calculate_step_and_side_dist_y(t_ray_data *data)
{
	if (data->ray_dir_y < 0)
	{
		data->step_y = -1;
		data->side_dist_y = (data->ray_y - data->map_y) * data->delta_dist_y;
	}
	else
	{
		data->step_y = 1;
		data->side_dist_y = (data->map_y + 1.0 - data->ray_y)
			* data->delta_dist_y;
	}
}

static void	perform_dda(t_config *config, t_ray_data *data)
{
	while (data->hit == 0)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_dist_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_dist_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
		if (is_wall(config, data->map_x, data->map_y))
			data->hit = 1;
	}
}

static void	distance_direction_utils(t_ray_data *data, t_ray *result,
			float perp_wall_dist)
{
	if (result->wall_x < 0)
		result->wall_x += 1.0;
	if (perp_wall_dist <= 0)
		result->distance = 0.1;
	else
		result->distance = perp_wall_dist;
	result->side = data->side;
}

static void	calculate_wall_distance_and_direction(t_ray_data *data,
			t_ray *result)
{
	float	perp_wall_dist;

	if (data->side == 0)
	{
		perp_wall_dist = (data->map_x - data->ray_x
				+ (1 - data->step_x) / 2) / data->ray_dir_x;
		result->wall_x = data->ray_y + perp_wall_dist * data->ray_dir_y;
		if (data->step_x == 1)
			result->wall_dir = 3;
		else
			result->wall_dir = 2;
	}
	else
	{
		perp_wall_dist = (data->map_y - data->ray_y
				+ (1 - data->step_y) / 2) / data->ray_dir_y;
		result->wall_x = data->ray_x + perp_wall_dist * data->ray_dir_x;
		if (data->step_y == 1)
			result->wall_dir = 0;
		else
			result->wall_dir = 1;
	}
	result->wall_x = result->wall_x - floor(result->wall_x);
	distance_direction_utils(data, result, perp_wall_dist);
}

t_ray	dda_cast_ray(t_config *config, float ray_angle)
{
	t_ray		result;
	t_ray_data	data;

	ft_memset(&result, 0, sizeof(t_ray));
	init_ray_data(&data, config, ray_angle);
	calculate_delta_dist(&data);
	calculate_step_and_side_dist_x(&data);
	calculate_step_and_side_dist_y(&data);
	perform_dda(config, &data);
	calculate_wall_distance_and_direction(&data, &result);
	result.map_x = data.map_x;
	result.map_y = data.map_y;
	result.angle = ray_angle;
	return (result);
}
