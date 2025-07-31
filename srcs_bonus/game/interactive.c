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

// Check if player is near an interactive element
t_interactive *get_nearby_interactive(t_config *config)
{
    t_interactive *current;
    float player_x, player_y;
    float distance;
    float interaction_range = 1.5f;

    player_x = config->player.pos_x;
    player_y = config->player.pos_y;
    current = config->game_state.interactives;

    while (current)
    {
        distance = sqrt((player_x - current->x - 0.5f) * (player_x - current->x - 0.5f) +
                       (player_y - current->y - 0.5f) * (player_y - current->y - 0.5f));
        
        if (distance <= interaction_range)
            return (current);
        current = current->next;
    }
    return (NULL);
}

// Handle lever activation
void activate_lever(t_config *config, t_interactive *lever)
{
    if (lever->type != INTERACTIVE_LEVER || lever->is_activated)
        return;

    lever->is_activated = 1;
    config->game_state.activated_levers++;
    
    printf("🔧 Lever activated! (%d/%d)\n", 
           config->game_state.activated_levers, config->game_state.total_levers);

    // Check if all levers are activated
    if (config->game_state.activated_levers >= config->game_state.total_levers)
    {
        unlock_all_doors(config);
        printf("🔓 All levers activated! Doors are now unlocked!\n");
    }
}

// Unlock all doors when all levers are activated
void unlock_all_doors(t_config *config)
{
    t_interactive *current;

    current = config->game_state.interactives;
    while (current)
    {
        if (current->type == INTERACTIVE_DOOR && 
            current->door_state == DOOR_CLOSED_LOCKED)
        {
            current->door_state = DOOR_CLOSED_UNLOCKED;
        }
        current = current->next;
    }
}

// Handle door interaction
void interact_with_door(t_config *config, t_interactive *door)
{
	(void)config;
    if (door->type != INTERACTIVE_DOOR)
        return;

    if (door->door_state == DOOR_CLOSED_LOCKED)
    {
        printf("🔒 Door is locked! Find and activate all levers first.\n");
    }
    else if (door->door_state == DOOR_CLOSED_UNLOCKED)
    {
        door->door_state = DOOR_OPENED_UNLOCKED;
        printf("🚪 Door opened!\n");
    }
    else
    {
        printf("🚪 Door is already open! Walk through to win!\n");
    }
}

// Check if player walked through an open door (win condition)
void check_door_win_condition(t_config *config)
{
    t_interactive *current;
    float player_x, player_y;
    float distance;

    if (config->game_state.game_won)
        return;

    player_x = config->player.pos_x;
    player_y = config->player.pos_y;
    current = config->game_state.interactives;

    while (current)
    {
        if (current->type == INTERACTIVE_DOOR && 
            current->door_state == DOOR_OPENED_UNLOCKED)
        {
            distance = sqrt((player_x - current->x - 0.5f) * (player_x - current->x - 0.5f) +
                           (player_y - current->y - 0.5f) * (player_y - current->y - 0.5f));
            
            if (distance <= 0.7f)  // Very close to door center
            {
                config->game_state.game_won = 1;
                printf("🎉 CONGRATULATIONS! YOU WON! 🎉\n");
                printf("You successfully activated all levers and escaped through the door!\n");
                // You could add a win screen or exit here
                return;
            }
        }
        current = current->next;
    }
}

// Main interaction handler
void handle_interaction(t_config *config)
{
    t_interactive *nearby;

    nearby = get_nearby_interactive(config);
    if (!nearby)
    {
        printf("💭 Nothing to interact with nearby.\n");
        return;
    }

    if (nearby->type == INTERACTIVE_LEVER)
    {
        if (nearby->is_activated)
            printf("🔧 This lever is already activated.\n");
        else
            activate_lever(config, nearby);
    }
    else if (nearby->type == INTERACTIVE_DOOR)
    {
        interact_with_door(config, nearby);
    }
}
