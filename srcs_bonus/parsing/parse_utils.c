/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:11:09 by rboland           #+#    #+#             */
/*   Updated: 2025/07/18 10:11:09 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_config_line(const char *line)
{
	return (ft_strncmp(line, "N ", 2) == 0
		|| ft_strncmp(line, "S ", 2) == 0
		|| ft_strncmp(line, "W ", 2) == 0
		|| ft_strncmp(line, "E ", 2) == 0
		|| ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0
		|| ft_strncmp(line, "DL ", 3) == 0
		|| ft_strncmp(line, "DU ", 3) == 0
		|| ft_strncmp(line, "DO ", 3) == 0
		|| ft_strncmp(line, "LON ", 4) == 0
		|| ft_strncmp(line, "LOS ", 4) == 0
		|| ft_strncmp(line, "LOB ", 4) == 0
		|| ft_strncmp(line, "LNN ", 4) == 0
		|| ft_strncmp(line, "LNS ", 4) == 0
		|| ft_strncmp(line, "LNB ", 4) == 0);
}

int	is_empty_line(const char *line)
{
	while (*line)
	{
		if (!ft_isspace((int)*line))
			return (0);
		line++;
	}
	return (1);
}
