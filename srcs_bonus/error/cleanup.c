/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:34:34 by rboland           #+#    #+#             */
/*   Updated: 2025/07/18 09:34:34 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void cleanup_interactives(t_config *config)
{
    t_interactive *current;
    t_interactive *next;

	if (!config)
        return;
    current = config->game_state.interactives;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    config->game_state.interactives = NULL;
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void cleanup_config(t_config *config)
{
    if (!config)
        return;
        
    if (config->north_texture)
        free(config->north_texture);
    if (config->south_texture)
        free(config->south_texture);
    if (config->west_texture)
        free(config->west_texture);
    if (config->east_texture)
        free(config->east_texture);
    if (config->floor_texture)
        free(config->floor_texture);
    if (config->ceiling_texture)
        free(config->ceiling_texture);
        
    if (config->door_locked_texture)
        free(config->door_locked_texture);
    if (config->door_unlocked_texture)
        free(config->door_unlocked_texture);
    if (config->door_open_texture)
        free(config->door_open_texture);
    if (config->lever_off_north_texture)
        free(config->lever_off_north_texture);
    if (config->lever_off_south_texture)
        free(config->lever_off_south_texture);
    if (config->lever_off_base_texture)
        free(config->lever_off_base_texture);
    if (config->lever_on_north_texture)
        free(config->lever_on_north_texture);
    if (config->lever_on_south_texture)
        free(config->lever_on_south_texture);
    if (config->lever_on_base_texture)
        free(config->lever_on_base_texture);
        
    if (config->map)
    {
        ft_free_split(config->map);
        config->map = NULL;
    }
    cleanup_interactives(config);
    get_next_line(-42);
    config->map_width = 0;
    config->map_height = 0;
}
