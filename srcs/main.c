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
	t_config config;

	// Appel aux fonctions de parsing et d'initialisation

	if (file_checker(argv[1], argc))
		return (1);
	// main game loop

	// Cleanup and exit

	return (0);
}
