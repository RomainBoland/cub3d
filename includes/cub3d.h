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


# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define PI 3.14159265359
# define MOVE_SPEED 0.04f
# define ROT_SPEED 0.03f
# define TEXTURE_SIZE 64

# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115  
# define D_KEY 100
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

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

typedef struct s_texture
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}	t_texture;

typedef struct s_tex
{
    t_texture   north;
    t_texture   south;
    t_texture   west;
    t_texture   east;
}   t_tex;

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
    int			map_width;
    int			map_height;
	t_tex		tex;
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

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_ray
{
    float   distance;
    int     side;           // 0 = vertical wall, 1 = horizontal wall
    float   wall_x;         // where exactly the wall was hit
    int     wall_dir;       // which direction: 0=North, 1=South, 2=East, 3=West
}	t_ray;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_data      img;
    t_config    *config;
    int         key_w;
    int         key_a;
    int         key_s;
    int         key_d;
    int         key_left;
    int         key_right;
}	t_game;

/* ------------	*/
/* 	FUNCTIONS	*/
/* ------------ */

// main.c
int				main(int argc, char **argv);

/*	ERROR	*/
// print_error.c
void			print_error(const char *message);
int				exit_error(const char *message, t_config *config);
// cleanup.c
void			cleanup_config(t_config *config);
void			ft_free_split(char **split);

/*	UTILS	*/
// utils1.c
int				ft_isspace(int c);
size_t			get_line_width(const char *line);
int				is_valid_tab_format(char **rgb);

// normalize_line.c
char			*normalize_line(const char *line);

/*	INIT	*/
// init.c
void			init_config(t_config *config);
void			init_parse_state(t_parse_state *state);

// texture_loading.c
int				load_texture(void *mlx, t_texture *texture, char *path);
int				load_all_textures(void *mlx, t_config *config);
void			cleanup_textures(void *mlx, t_config *config);
unsigned int	get_texture_pixel(t_texture *texture, int x, int y);

/*	PARSING	*/
// parse_file.c
int				file_checker(const char *file_path, int argc, t_config *config);
int				parse_file(int fd, t_config *config, t_parse_state *state);

// fill_map.c
int				start_map_parsing(const char *line, t_config *config);
int				add_line_to_map(const char *line, t_config *config);
int				is_map_line(const char *line);

// parse_config_line.c
int				parse_config_line(char *line, t_config *config, t_parse_state *state);
int				parse_config_line2(char **tokens, t_config *config,
				t_parse_state *state);
int				parse_config_line3(char **tokens, t_config *config,
				t_parse_state *state);
int				parse_floor_color(char **tokens, t_config *config,
				t_parse_state *state);
void			handle_config_line(char *key, char *value, t_config *config,
				t_parse_state *state);

// parse_config_line2.c
void			affect_rgb(int marker, t_config *config, char **rgb);
int				validate_rgb(int r, int g, int b);
int				parse_ceiling_color(char **tokens, t_config *config,
				t_parse_state *state);
void			update_config_status(t_parse_state *state);

// parse_arg.c
int				open_map(const char *file_path);
int				str_ends_with(const char *str, const char *suffix);
int				arg_checker(int argc, const char *file_path);

// parse_map.c
int				validate_map(t_config *config);
int				validate_map_characters(t_config *config);
int				find_player(t_config *config);
void			set_player_angle(t_config *config);

// map_validation.c
int				check_walls_around_spaces(t_config *config);

// parse_map_utils.c
int				is_valid_char(char c);
int				is_position_valid(t_config *config, int x, int y);

// parse_utils.c
int				is_config_line(const char *line);
int				is_empty_line(const char *line);
int				all_config_complete(t_parse_state *state);
int				validate_complete_config(t_config *config);

// validate_textures.c
int				validate_all_textures(t_config *config);
int				validate_texture_path(void *mlx, char *path);

/*	GAME	*/
// game_loop.c
void			game_loop(t_config *config);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int 			game_loop_hook(t_game *game);

// raycasting.c
int				is_wall(t_config *config, int map_x, int map_y);
t_ray			dda_cast_ray(t_config *config, float ray_angle);
t_texture		*get_wall_texture(t_config *config, int wall_dir);
void 			render_textured_wall(t_config *config, t_data *img, int x, t_ray ray);
float			normalize_angle(float angle);
void			render_raycast(t_config *config, t_data *img);

// movement.c
int				is_valid_position(t_config *config, float x, float y);
void			move_player(t_config *config, float move_x, float move_y);
void			rotate_player(t_config *config, float rotation);

// events.c
int				handle_keypress(int keycode, t_game *game);
int				handle_keyrelease(int keycode, t_game *game);
int				close_window(t_game *game);
void			update_game(t_game *game);

#endif