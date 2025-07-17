/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:10:25 by rboland           #+#    #+#             */
/*   Updated: 2025/07/15 10:10:25 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ------------ */
/*	INCLUDES	*/
/* ------------	*/

# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

/* ------------	*/
/* 	STRUCTURES 	*/
/* ------------	*/

typedef struct s_config
{
    char    *north_texture;
    char    *south_texture;
    char    *west_texture;
    char    *east_texture;
    int     floor_color[3];     // RGB
    int     ceiling_color[3];   // RGB
    char    **map;
    int     map_width;
    int     map_height;
    // player start position and orientation
}   t_config;

/* ------------	*/
/* 	FUNCTIONS	*/
/* ------------ */

// main.c
int		main(int argc, char **argv);

/*	ERROR	*/
// print_error.c
void	print_error(const char *message);
int		exit_error(const char *message);

/*	PARSING	*/
// parse_file.c
int		open_map(const char *file_path);
int		str_ends_with(const char *str, const char *suffix);
int		arg_checker(int argc, const char *file_path);
int		file_checker(const char *file_path, int argc);

// 

# endif