/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:50:05 by rboland           #+#    #+#             */
/*   Updated: 2025/01/30 10:51:55 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;

	if (!dst && !src)
		return (dst);
	temp_dst = (unsigned char *)dst;
	temp_src = (unsigned char *)src;
	while (size > 0)
	{
		*(temp_dst++) = *(temp_src++);
		size--;
	}
	return (dst);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, const char *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen_gnl(s1);
	len2 = ft_strlen_gnl(s2);
	str = malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	free(s1);
	return (str);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	if (start > ft_strlen_gnl(s))
		return (ft_strdup_gnl(""));
	if (len > ft_strlen_gnl(s + start))
		len = ft_strlen_gnl(s + start);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	tmp_c;

	tmp_c = (char)c;
	i = 0;
	while (s && s[i])
	{
		if (s[i] == tmp_c)
			return ((char *)&s[i]);
		i++;
	}
	if (s && s[i] == tmp_c)
		return ((char *)&s[i]);
	return (NULL);
}
