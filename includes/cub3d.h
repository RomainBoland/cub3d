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

# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

/* ---------- */
/* STRUCTURES */
/* ---------- */

/* ------------ */
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