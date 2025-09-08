/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:43:44 by rboland           #+#    #+#             */
/*   Updated: 2025/07/31 11:43:44 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_interactive	*get_nearby_interactive(t_config *config)
{
	t_interactive	*current;
	float			player_x;
	float			player_y;
	float			distance;
	float			interaction_range;

	interaction_range = 1.5f;
	player_x = config->player.pos_x;
	player_y = config->player.pos_y;
	current = config->game_state.interactives;
	while (current)
	{
		distance = sqrt((player_x - current->x - 0.5f)
				* (player_x - current->x - 0.5f)
				+ (player_y - current->y - 0.5f)
				* (player_y - current->y - 0.5f));
		if (distance <= interaction_range)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	activate_lever(t_config *config, t_interactive *lever)
{
	if (lever->type != INTERACTIVE_LEVER || lever->is_activated)
		return ;
	lever->is_activated = 1;
	config->game_state.activated_levers++;
	printf("🔧 Lever activated! (%d/%d)\n",
		config->game_state.activated_levers, config->game_state.total_levers);
	if (config->game_state.activated_levers >= config->game_state.total_levers)
	{
		unlock_all_doors(config);
		printf("🔓 All levers activated! Doors are now unlocked!\n");
	}
}

void	unlock_all_doors(t_config *config)
{
	t_interactive	*current;

	current = config->game_state.interactives;
	while (current)
	{
		if (current->type == INTERACTIVE_DOOR
			&& current->door_state == DOOR_CLOSED_LOCKED)
		{
			current->door_state = DOOR_CLOSED_UNLOCKED;
		}
		current = current->next;
	}
}

void	interact_with_door(t_config *config, t_interactive *door)
{
	(void)config;
	if (door->type != INTERACTIVE_DOOR)
		return ;
	if (door->door_state == DOOR_CLOSED_LOCKED)
	{
		printf("🔒 Door is locked! Find and activate all levers first.\n");
	}
	else if (door->door_state == DOOR_CLOSED_UNLOCKED)
		door->door_state = DOOR_OPENED_UNLOCKED;
	else
	{
		printf("🚪 Door is already open! Walk through to win!\n");
	}
}

void	handle_interaction(t_config *config)
{
	t_interactive	*nearby;

	nearby = get_nearby_interactive(config);
	if (!nearby)
	{
		printf("💭 Nothing to interact with nearby.\n");
		return ;
	}
	if (nearby->type == INTERACTIVE_DOOR)
	{
		interact_with_door(config, nearby);
	}
	else if (nearby->type == INTERACTIVE_LEVER)
	{
		if (nearby->is_activated)
			printf("🔧 This lever is already activated.\n");
		else
			activate_lever(config, nearby);
	}
}
