/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:34:33 by rboland           #+#    #+#             */
/*   Updated: 2025/07/31 11:34:33 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_interactive *create_interactive(int x, int y, t_interactive_type type)
{
    t_interactive *new_elem;

    new_elem = malloc(sizeof(t_interactive));
    if (!new_elem)
        return (NULL);
    new_elem->x = x;
    new_elem->y = y;
    new_elem->type = type;
    new_elem->is_activated = 0;
    new_elem->door_state = DOOR_CLOSED_LOCKED;
    new_elem->next = NULL;
    return (new_elem);
}

void add_interactive_to_list(t_config *config, t_interactive *new_elem)
{
    t_interactive *current;

    if (!config->game_state.interactives)
    {
        config->game_state.interactives = new_elem;
        return;
    }
    current = config->game_state.interactives;
    while (current->next)
        current = current->next;
    current->next = new_elem;
}

void scan_for_interactive_elements(t_config *config)
{
    int x, y;
    t_interactive *new_elem;

    config->game_state.total_levers = 0;
    config->game_state.activated_levers = 0;
    config->game_state.game_won = 0;
    config->game_state.interactives = NULL;

    y = 0;
    while (y < config->map_height)
    {
        x = 0;
        while (x < (int)ft_strlen(config->map[y]))
        {
            if (config->map[y][x] == 'L')  // Lever
            {
                new_elem = create_interactive(x, y, INTERACTIVE_LEVER);
                if (new_elem)
                {
                    add_interactive_to_list(config, new_elem);
                    config->game_state.total_levers++;
                }
            }
            else if (config->map[y][x] == 'D')  // Door
            {
                new_elem = create_interactive(x, y, INTERACTIVE_DOOR);
                if (new_elem)
                    add_interactive_to_list(config, new_elem);
            }
            x++;
        }
        y++;
    }
}
