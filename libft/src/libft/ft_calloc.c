/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:24:40 by rboland           #+#    #+#             */
/*   Updated: 2024/10/20 09:32:43 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	while (i < size * count)
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}
/*
#include <stdio.h>

int main(void)
{
    int *arr;
    size_t count = 100;
    size_t size = sizeof(int);

    arr = ft_calloc(count, size);
    if (arr == NULL)
    {
        printf("Allocation failed\n");
        return (1);
    }
    for (size_t i = 0; i < count; i++)
    {
        printf("arr[%zu] = %d\n", i, arr[i]);
    }
    free(arr);
    return (0);
}
*/
