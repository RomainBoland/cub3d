/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:24:46 by rboland           #+#    #+#             */
/*   Updated: 2025/07/19 17:24:46 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	dda_cast_ray(t_config *config, float ray_angle)
{
	// direction du rayon
	float ray_dir_x = cos(ray_angle); // donne l'angle en chiffre au lieu de l'angle en degres
	float ray_dir_y = sin(ray_angle);

	// position actuelle du rayon
	float ray_x = config->player.pos_x; // milieu de la case
	float ray_y = config->player.pos_y;

	// Quelle case du grid on est
	int map_x = (int)ray_x;
	int map_y = (int)ray_y;

	// Longueur du rayon de la position actuelle en x ou y
	float side_dist_x;
	float side_dist_y;

	// longueur du rayon dans la direction x ou y jusqu'a la prochaine case
	// fabs (ou arc tangente) donne la taille reelle (ici la distance parcourue) d'un rayon a l'angle A (A = ray_dir_x ou ray_dir_y) 
	// jusqu'a une certaine distance (ici 1, car on avance une case par une case)
	// par exemple, si ray_dir_x = 0.5, alors delta_dist_x = 2, car on avance de 2 cases en x pour chaque case en y
	float delta_dist_x = fabs(1 / ray_dir_x);
	float delta_dist_y = fabs(1 / ray_dir_y);

	// Quelle direction on avance ?
	int step_x;
	int step_y;

	// calculer le prochain pas (CF -1 ou +1 en x ou y) et la distance initiale
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (ray_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - ray_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (ray_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - ray_y) * delta_dist_y;
	}

	// Maintenant qu'on a toutes les infos, on peut faire le DDA
	int hit; // est ce qu on a touche un mur ?
	int side; // est ce qu'on a touche un mur vertical ou horizontal ?

	hit = 0;
	while (hit == 0)
	{
		// jump vers la prochaine intersection, soit x ou y
		if (side_dist_x < side_dist_y) // SI la distance en x jusqu a la prochaine case, on avance en x
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0; // vertical
		}
		else // SI la distance en y jusqu a la prochaine case, on avance en y
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1; // horizontal
		}
		// Check si on a touche un mur
		if (map_y >= 0 && map_y < config->map_height &&
			map_x >= 0 && map_x < (int)ft_strlen(config->map[map_y]) &&
			config->map[map_y][map_x] == '1') // 1 = mur
			hit = 1; // on a touche un mur
	}

	// ENFIN, on calcule la distance du rayon
	float perp_wall_dist;
	if (side == 0) // SI vertical
		perp_wall_dist = (map_x - ray_x + (1 - step_x) / 2) / ray_dir_x; // correction pour le pas
	else // SI horizontal
		perp_wall_dist = (map_y - ray_y + (1 - step_y) / 2) / ray_dir_y; // correction pour le pas
	
	return perp_wall_dist; // retourne la distance du mur
	// Note: on pourrait aussi retourner le type de mur, mais pour l'instant on s'en fiche
}

void	render_raycast(t_config *config, t_data *img)
{
	int	f_color;
	int	c_color;
	int	x;

	f_color = (config->floor_color[0] << 16) | (config->floor_color[1] << 8) | config->floor_color[2];
	c_color = (config->ceiling_color[0] << 16) | (config->ceiling_color[1] << 8) | config->ceiling_color[2];
	x = 0;

	while (x < 1920)
	{
		// premiere etape : calculer la largeur du FOV
		float camera_x = 2 * x / (float)1920 - 1; // coordonnee en x de la camera
		float ray_angle = config->player.angle + atan(camera_x * tan(PI / 6)); // FOV = 60 degrees

		// deuxieme etape : calculer la distance jusqu'au mur par rayon
		float distance = dda_cast_ray(config, ray_angle);

		// calculer la hauteur du mur
		int wall_height = (int)(1080 / distance); // 1080 est la hauteur de la fenetre
		if (wall_height > 1080)
			wall_height = 1080;
		
		int wall_start = (1080 - wall_height) / 2; // position de depart du mur
		int wall_end = wall_start + wall_height; // position de fin du mur

		// Dessiner le plafond
        for (int y = 0; y < wall_start; y++)
            my_mlx_pixel_put(img, x, y, c_color);
        
        // Dessiner le mur (gris pour l'instant)
        for (int y = wall_start; y < wall_end; y++)
            my_mlx_pixel_put(img, x, y, 0x808080); // Gray
        
        // Dessiner le sol
        for (int y = wall_end; y < 1080; y++)
            my_mlx_pixel_put(img, x, y, f_color);
		x++;
	}
}
