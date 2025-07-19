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

typedef struct s_player
{
    int     x;          // Player grid position
    int     y;
    char    direction;  // N, S, E, W
    float   pos_x;      // Actual position for raycasting
    float   pos_y;
    float   angle;      // Viewing angle in radians
}   t_player;

typedef struct s_tex
{
	void	*north_img;		// A FREE
	void	*south_img;		// A FREE
	void	*west_img;		// A FREE
	void	*east_img;		// A FREE
}	t_tex;

// contient les configurations du jeu

typedef struct s_config
{
    char		*north_texture;		// A FREE
    char		*south_texture;		// A FREE
    char		*west_texture;		// A FREE
    char		*east_texture;		// A FREE
    int			floor_color[3];     // RGB, A FREE
    int			ceiling_color[3];   // RGB, A FREE
    char		**map;				// A FREE
    size_t		map_width;
    size_t		map_height;
    t_player	player;
}   t_config;

// contient l'état du parsing
typedef struct s_parse_state
{
    int north_found;
    int south_found;
    int west_found;
    int east_found;
    int floor_found;
    int ceiling_found;
    int all_config_found;
}   t_parse_state;

/* ------------	*/
/* 	FUNCTIONS	*/
/* ------------ */

// main.c
int		main(int argc, char **argv);

/*	ERROR	*/
// print_error.c
void	print_error(const char *message);
int		exit_error(const char *message, t_config *config);
// cleanup.c
void	cleanup_config(t_config *config);
void	ft_free_split(char **split);

/*	UTILS	*/
// utils1.c
int		ft_isspace(int c);
size_t get_line_width(const char *line);

/*	INIT	*/
// init.c
void	init_config(t_config *config);
void	init_parse_state(t_parse_state *state);

/*	PARSING	*/
// parse_file.c
int		add_line_to_map(const char *line, t_config *config);
int		start_map_parsing(const char *line, t_config *config);
int		parse_file(int fd, t_config *config, t_parse_state *state);
int		parse_file2(char *line, t_config *config, int fd);
int		file_checker(const char *file_path, int argc, t_config *config);

// parse_config_line.c
int		validate_rgb(int r, int g, int b);
int		parse_config_line(char *line, t_config *config, t_parse_state *state);
int		parse_config_line2(char **tokens, t_config *config, t_parse_state *	state);
int		parse_config_line3(char **tokens, t_config *config, t_parse_state *state);

// parse_arg.c
int		open_map(const char *file_path);
int		str_ends_with(const char *str, const char *suffix);
int		arg_checker(int argc, const char *file_path);

// parse_utils.c
int		is_config_line(const char *line);
int		is_empty_line(const char *line);
int		is_map_line(const char *line);
int		all_config_complete(t_parse_state *state);
int		validate_complete_config(t_config *config);

# endif