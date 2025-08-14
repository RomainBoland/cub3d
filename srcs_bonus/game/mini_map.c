/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:46:37 by nsaillez          #+#    #+#             */
/*   Updated: 2025/08/14 10:23:07 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// Vérifie si un angle est dans le champ de vision
static int is_angle_in_fov(float angle, float fov_start, float fov_end)
{
    angle = normalize_angle(angle);
    fov_start = normalize_angle(fov_start);
    fov_end = normalize_angle(fov_end);
    
    if (fov_start < fov_end)
        return (angle >= fov_start && angle <= fov_end);
    else
        return (angle >= fov_start || angle <= fov_end);
}

// Initialise les données de la minimap
static void init_minimap_data(t_minimap_data *data, t_config *config)
{
    data->player_x = config->player.pos_x;
    data->player_y = config->player.pos_y;
    data->player_angle = config->player.angle;
    data->center_x = MINIMAP_RADIUS;
    data->center_y = MINIMAP_RADIUS;
    data->scale = (float)MINIMAP_RADIUS / MINIMAP_TILES_RADIUS;
    
    // Calcul du champ de vision en radians
    data->fov_start = normalize_angle(data->player_angle - FOV_HALF_TAN);
    data->fov_end = normalize_angle(data->player_angle + FOV_HALF_TAN);
}

// Convertit les coordonnées écran de la minimap en coordonnées monde
static void screen_to_world(t_minimap_data *data, int screen_x, int screen_y, 
                           float *world_x, float *world_y)
{
    // Distance du centre en pixels
    float pixel_x = screen_x - data->center_x;
    float pixel_y = screen_y - data->center_y;
    
    // Conversion en coordonnées monde (carte fixe, pas de rotation)
    *world_x = data->player_x + (pixel_x / data->scale);
    *world_y = data->player_y + (pixel_y / data->scale);
}

// Obtient la couleur d'une cellule de la carte
static unsigned int get_map_cell_color(t_config *config, int map_x, int map_y)
{
    t_interactive *interactive;
    char cell;
    
    // Vérification des limites
    if (map_y < 0 || map_y >= config->map_height)
        return (COLOR_BACKGROUND);
    if (map_x < 0 || map_x >= (int)ft_strlen(config->map[map_y]))
        return (COLOR_BACKGROUND);
    
    cell = config->map[map_y][map_x];
    
    switch (cell)
    {
        case '1':
            return (COLOR_WALL);
        case '0':
        case 'N':
        case 'S':
        case 'E':
        case 'W':
            return (COLOR_EMPTY);
        case 'D':
            interactive = find_interactive_at(config, map_x, map_y);
            if (interactive)
            {
                switch (interactive->door_state)
                {
                    case DOOR_CLOSED_LOCKED:
                        return (COLOR_DOOR_LOCKED);
                    case DOOR_CLOSED_UNLOCKED:
                        return (COLOR_DOOR_UNLOCKED);
                    case DOOR_OPENED_UNLOCKED:
                        return (COLOR_DOOR_OPEN);
                }
            }
            return (COLOR_WALL);
        case 'L':
            interactive = find_interactive_at(config, map_x, map_y);
            if (interactive)
            {
                return (interactive->is_activated ? COLOR_LEVER_ON : COLOR_LEVER_OFF);
            }
            return (COLOR_WALL);
        default:
            return (COLOR_BACKGROUND);
    }
}

// Dessine un pixel sur la minimap avec les coordonnées d'écran
static void draw_minimap_pixel(t_game *game, int x, int y, unsigned int color)
{
    my_mlx_pixel_put(&game->img, x + MINIMAP_OFFSET_X, y + MINIMAP_OFFSET_Y, color);
}

// Mélange deux couleurs (pour la surimpression du FOV)
// static unsigned int blend_colors(unsigned int base_color, unsigned int overlay_color)
// {
//     unsigned int alpha = (overlay_color >> 24) & 0xFF;
//     if (alpha == 0)
//         return (base_color);
    
//     unsigned int r_base = (base_color >> 16) & 0xFF;
//     unsigned int g_base = (base_color >> 8) & 0xFF;
//     unsigned int b_base = base_color & 0xFF;
    
//     unsigned int r_overlay = (overlay_color >> 16) & 0xFF;
//     unsigned int g_overlay = (overlay_color >> 8) & 0xFF;
//     unsigned int b_overlay = overlay_color & 0xFF;
    
//     // Mélange simple avec alpha
//     unsigned int r = (r_overlay * alpha + r_base * (255 - alpha)) / 255;
//     unsigned int g = (g_overlay * alpha + g_base * (255 - alpha)) / 255;
//     unsigned int b = (b_overlay * alpha + b_base * (255 - alpha)) / 255;
    
//     return ((r << 16) | (g << 8) | b);
// }

// Dessine la géométrie de la carte sur la minimap
static void draw_map_geometry(t_game *game, t_minimap_data *data)
{
    int x, y;
    float world_x, world_y;
    int map_x, map_y;
    unsigned int map_color;
    float distance_sq;
    
    for (y = 0; y < MINIMAP_SIZE; y++)
    {
        for (x = 0; x < MINIMAP_SIZE; x++)
        {
            // Vérifier si on est dans le cercle
            distance_sq = (x - data->center_x) * (x - data->center_x) + 
                         (y - data->center_y) * (y - data->center_y);
            
            if (distance_sq <= MINIMAP_RADIUS * MINIMAP_RADIUS)
            {
                // Convertir les coordonnées écran en coordonnées monde
                screen_to_world(data, x, y, &world_x, &world_y);
                
                map_x = (int)world_x;
                map_y = (int)world_y;
                
                // Obtenir la couleur de la cellule
                map_color = get_map_cell_color(game->config, map_x, map_y);
                
                draw_minimap_pixel(game, x, y, map_color);
            }
        }
    }
}

// Dessine le champ de vision du joueur
static void draw_fov_overlay(t_game *game, t_minimap_data *data)
{
    int x, y;
    float distance_sq;
    float angle_to_pixel;
    float dx, dy;
    
    for (y = 0; y < MINIMAP_SIZE; y++)
    {
        for (x = 0; x < MINIMAP_SIZE; x++)
        {
            distance_sq = (x - data->center_x) * (x - data->center_x) + 
                         (y - data->center_y) * (y - data->center_y);
            
            if (distance_sq <= MINIMAP_RADIUS * MINIMAP_RADIUS && distance_sq > 0)
            {
                // Calculer l'angle depuis le joueur vers ce pixel
                dx = x - data->center_x;
                dy = y - data->center_y;
                angle_to_pixel = atan2(dy, dx);
                
                // Vérifier si l'angle est dans le FOV
                if (is_angle_in_fov(angle_to_pixel, data->fov_start, data->fov_end))
                {
                    // Appliquer une surimpression bleue semi-transparente
                    draw_minimap_pixel(game, x, y, COLOR_FOV);
                }
            }
        }
    }
}

// Dessine la bordure de la minimap
static void draw_minimap_border(t_game *game, t_minimap_data *data)
{
    int x, y;
    float distance_sq;
    float inner_radius_sq = (MINIMAP_RADIUS - 2) * (MINIMAP_RADIUS - 2);
    float outer_radius_sq = MINIMAP_RADIUS * MINIMAP_RADIUS;
    
    for (y = 0; y < MINIMAP_SIZE; y++)
    {
        for (x = 0; x < MINIMAP_SIZE; x++)
        {
            distance_sq = (x - data->center_x) * (x - data->center_x) + 
                         (y - data->center_y) * (y - data->center_y);
            
            if (distance_sq <= outer_radius_sq && distance_sq >= inner_radius_sq)
            {
                draw_minimap_pixel(game, x, y, COLOR_BORDER);
            }
        }
    }
}

// Dessine le joueur au centre
static void draw_player(t_game *game, t_minimap_data *data)
{
    int x, y;
    float distance_sq;
    int player_radius = 3;
    int i;
    
    // Dessiner le point du joueur
    for (y = data->center_y - player_radius; y <= data->center_y + player_radius; y++)
    {
        for (x = data->center_x - player_radius; x <= data->center_x + player_radius; x++)
        {
            if (x >= 0 && x < MINIMAP_SIZE && y >= 0 && y < MINIMAP_SIZE)
            {
                distance_sq = (x - data->center_x) * (x - data->center_x) + 
                             (y - data->center_y) * (y - data->center_y);
                
                if (distance_sq <= player_radius * player_radius)
                {
                    draw_minimap_pixel(game, x, y, COLOR_PLAYER);
                }
            }
        }
    }
    
    // Dessiner une ligne indiquant la direction du regard
    int dir_length = 12;
    for (i = 0; i <= dir_length; i++)
    {
        int px = data->center_x + (int)(i * cos(data->player_angle));
        int py = data->center_y + (int)(i * sin(data->player_angle));
        
        if (px >= 0 && px < MINIMAP_SIZE && py >= 0 && py < MINIMAP_SIZE)
        {
            draw_minimap_pixel(game, px, py, COLOR_PLAYER);
        }
    }
}

// Fonction principale pour mettre à jour la minimap
void update_mini_map(t_game *game)
{
    t_minimap_data data;
    
    // Initialiser les données
    init_minimap_data(&data, game->config);
    
    // Dessiner les différentes couches dans l'ordre
    draw_map_geometry(game, &data);    // Géométrie de base (carte fixe)
    draw_fov_overlay(game, &data);     // Surimpression du FOV
    draw_minimap_border(game, &data);  // Bordure
    draw_player(game, &data);          // Joueur (en dernier)
}
