/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:54:25 by rboland           #+#    #+#             */
/*   Updated: 2024/10/20 10:54:27 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(const char *set, char c);
static char	*to_trim(const char *s1, size_t start, size_t len);

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		end;

	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	i = 0;
	end = ft_strlen(s1) - 1;
	while (is_set(set, s1[i]) && i <= end)
		i++;
	while (is_set(set, s1[end]) && end >= i)
		end--;
	return (to_trim(s1, i, end - i + 1));
}

static char	*to_trim(const char *s1, size_t start, size_t len)
{
	char	*str;
	size_t	i;

	if (len == 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	i = 0;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s1[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	is_set(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int main(void)
{
	char	*str = "aaabababbaJAYSONabbabbba";
	char	*set = "ab";
	char	*strtrim;

	strtrim = ft_strtrim(str, set);
	if (strtrim)
	{
		printf("%s\n", strtrim);
		free(strtrim);
	}
	else
	{
		printf("Allocation failed.\n");
	}
	return (0);
}
*/
