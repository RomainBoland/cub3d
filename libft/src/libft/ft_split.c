/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:43:52 by rboland           #+#    #+#             */
/*   Updated: 2025/01/04 15:57:45 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char *str, char charset)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] != charset && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (str[i] == charset)
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*ft_get_word(char *str, char charset, int *index)
{
	int		start;
	int		word_size;
	char	*word;
	int		i;

	i = 0;
	word_size = 0;
	while (str[*index] && str[*index] == charset)
		(*index)++;
	start = *index;
	while (str[*index] && str[*index] != charset)
	{
		word_size++;
		(*index)++;
	}
	word = (char *)malloc(sizeof(char) * (word_size + 1));
	if (!word)
		return (NULL);
	while (i < word_size)
	{
		word[i] = str[start + i];
		i++;
	}
	word[word_size] = '\0';
	return (word);
}

static void	ft_free(char **str, int len)
{
	while (len > 0)
	{
		len--;
		free(str[len]);
	}
	free(str);
}

char	**ft_split(char *str, char charset)
{
	int		i;
	int		index;
	char	**split_tab;
	int		words;

	if (!str)
		return (NULL);
	words = ft_count_words(str, charset);
	split_tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split_tab)
		return (NULL);
	i = 0;
	index = 0;
	while (i < words)
	{
		split_tab[i] = ft_get_word(str, charset, &index);
		if (!split_tab[i])
		{
			ft_free(split_tab, i);
			return (NULL);
		}
		i++;
	}
	split_tab[i] = (NULL);
	return (split_tab);
}
/*
#include <stdio.h>
int main(void)
{
    char    *str = NULL;
	char	charset = 'x';
    char    **result;
    size_t i;

    result = ft_split(str, charset);
	if (!result)
	{
		printf("tab = NULL");
		return (1);
	}
	i = 0;
    while (result[i])
    {
        printf("result[%zu] : %s\n", i, result[i]);
        free(result[i]);
        i++;
    }
    free(result);
    return (0);
}
*/
