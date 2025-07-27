/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:47:42 by rboland           #+#    #+#             */
/*   Updated: 2025/07/27 16:38:21 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup_gnl(char *src)
{
	int		i;
	int		len;
	char	*copy;

	if (!src)
		return (NULL);
	len = ft_strlen_gnl(src);
	i = 0;
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	while (src[i])
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static int	init_and_read(int fd, char **stash, char *buff)
{
	int	bytes_read;

	if (!(*stash))
	{
		*stash = ft_strdup_gnl("");
		if (!(*stash))
			return (-1);
	}
	bytes_read = read(fd, buff, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		if (bytes_read == 0 && *stash && **stash)
			return (0);
		free(*stash);
		*stash = NULL;
		return (-1);
	}
	if (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		*stash = ft_strjoin_gnl(*stash, buff);
		if (!(*stash))
			return (-1);
	}
	return (bytes_read);
}

static char	*get_line_and_update_stash(char **stash, char *newline_pos)
{
	char	*new_stash;
	char	*line;

	if (newline_pos)
	{
		line = ft_substr(*stash, 0, newline_pos - *stash + 1);
		new_stash = ft_strdup_gnl(newline_pos + 1);
		free(*stash);
		*stash = new_stash;
	}
	else
	{
		line = ft_strdup_gnl(*stash);
		free(*stash);
		*stash = NULL;
	}
	return (line);
}

char	*free_stash_error(int fd, char **stash)
{
	int	i;

	i = 0;
	if (fd == -42)
	{
		while (i < OPEN_MAX)
		{
			if (stash[i])
			{
				free(stash[i]);
				stash[i] = NULL;
			}
			i++;
		}
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*stash[OPEN_MAX];
	char		*newline_pos;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_stash_error(fd, stash));
	while (1)
	{
		newline_pos = ft_strchr(stash[fd], '\n');
		if (newline_pos)
			return (get_line_and_update_stash(&stash[fd], newline_pos));
		bytes_read = init_and_read(fd, &stash[fd], buff);
		if (bytes_read < 0 || !stash[fd])
			return (NULL);
		if (bytes_read == 0 && stash[fd] && *stash[fd])
			return (get_line_and_update_stash(&stash[fd], NULL));
		if (bytes_read == 0 && stash[fd] && *stash[fd] == '\0')
		{
			free(stash[fd]);
			stash[fd] = NULL;
		}
		if (bytes_read == 0)
			return (NULL);
	}
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	char	*result1;
	char	*result2;
	int		fd1, fd2;
	int		line = 1;

	// Ouvrir les fichiers une seule fois
	fd1 = open("test.txt", O_RDONLY);
	if (fd1 == -1)
	{
		perror("Erreur lors de l'ouverture de test.txt");
		return (1);
	}
	fd2 = open("test2.txt", O_RDONLY);
	if (fd2 == -1)
	{
		perror("Erreur lors de l'ouverture de test2.txt");
		close(fd1);
		return (1);
	}
	result1 = get_next_line(fd1);
	result2 = get_next_line(fd2);

	// Lire et afficher les lignes des deux fichiers
	while (result1 || result2)
	{
		if (result1)
		{
			printf("Fichier test.txt, ligne %d : %s", line, result1);
			free(result1);
			result1 = get_next_line(fd1);
		}
		else
			printf("Fichier test.txt, ligne %d : (fin de fichier)\n", line);

		if (result2)
		{
			printf("Fichier test2.txt, ligne %d : %s", line, result2);
			free(result2);
			result2 = get_next_line(fd2);
		}
		else
			printf("Fichier test2.txt, ligne %d : (fin de fichier)\n", line);

		line++;
	}

	free(result1);
	free(result2);

	// Fermer les fichiers
	close(fd1);
	close(fd2);
	return (0);
}*/
