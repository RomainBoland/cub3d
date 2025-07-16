/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:34:50 by rboland           #+#    #+#             */
/*   Updated: 2024/10/21 09:48:50 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_nbrs(int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	fill_tab(char *tab, int n, size_t len, int sign)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		tab[len - i - 1] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	if (sign)
		tab[0] = '-';
	tab[len] = '\0';
}

char	*ft_itoa(int n)
{
	char	*tab;
	size_t	len;
	int		sign;

	sign = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		len = 1;
		n = -n;
		sign = 1;
	}
	else
		len = 0;
	len += count_nbrs(n);
	tab = (char *)malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	fill_tab(tab, n, len, sign);
	return (tab);
}
/*
int	main(void)
{
	int	n = 1576;
	char *tab;

	tab = ft_itoa(n);
	printf("%s\n", tab);
	return (0);
}
*/
