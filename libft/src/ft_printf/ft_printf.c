/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:56:48 by rboland           #+#    #+#             */
/*   Updated: 2024/10/25 12:56:50 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_finder(char form_spec, va_list args)
{
	if (form_spec == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
		return (1);
	}
	else if (form_spec == 's')
		return (ft_put_str(va_arg(args, char *)));
	else if (form_spec == 'p')
		return (ft_put_ptr(va_arg(args, void *)));
	else if (form_spec == 'd' || form_spec == 'i')
		return (ft_put_int(va_arg(args, int)));
	else if (form_spec == 'u')
		return (ft_put_unsigned(va_arg(args, unsigned int)));
	else if (form_spec == 'x')
		return (ft_put_hexa(va_arg(args, ssize_t), 0));
	else if (form_spec == 'X')
		return (ft_put_hexa(va_arg(args, ssize_t), 1));
	else if (form_spec == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	args;
	int		count;

	i = 0;
	va_start(args, format);
	count = 0;
	while (format[i])
	{
		if (format[i] != '%')
		{
			ft_putchar_fd(format[i], 1);
			count++;
		}
		else
		{
			i++;
			count += format_finder(format[i], args);
		}
		i++;
	}
	va_end(args);
	return (count);
}
