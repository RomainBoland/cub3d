/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:44:13 by rboland           #+#    #+#             */
/*   Updated: 2025/07/19 16:44:13 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_expanded_length(const char *line)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			len += 4;
		else
			len++;
		i++;
	}
	return (len);
}

static void	expand_tabs(const char *line, char *normalized)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\t')
		{
			k = 0;
			while (k < 4)
			{
				normalized[j++] = ' ';
				k++;
			}
		}
		else
			normalized[j++] = line[i];
		i++;
	}
	normalized[j] = '\0';
}

char	*normalize_line(const char *line)
{
	char	*normalized;
	int		expanded_len;

	if (!line)
		return (NULL);
	expanded_len = count_expanded_length(line);
	normalized = malloc(sizeof(char) * (expanded_len + 1));
	if (!normalized)
		return (NULL);
	expand_tabs(line, normalized);
	return (normalized);
}
