/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:10:08 by rboland           #+#    #+#             */
/*   Updated: 2025/07/15 10:10:08 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3d <path_to_map_file.cub>\n", 2);
		return (1);
	}
	ft_putstr_fd("Game started with map: ", 1);
	ft_putstr_fd(argv[1], 1);
	ft_putchar_fd('\n', 1);

	return (0);
}
