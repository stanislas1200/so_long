/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:14:21 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/29 13:09:51 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "ft_printf.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write (1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	format(char *c, va_list vl)
{
	size_t	len;

	len = 0;
	if (*c == 'd' || *c == 'i')
		len = ft_putnbr(va_arg(vl, int));
	else if (*c == 'c')
		len = ft_putchar(va_arg(vl, int));
	else if (*c == 's')
		len = ft_putstr(va_arg(vl, char *));
	return (len);
}

int	ft_printf(const char *s, ...)
{
	va_list	vl;
	size_t	len;

	len = 0;
	va_start(vl, s);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			len += format((char *)s, vl);
		}
		else
		{
			write(1, s, 1);
			len++;
		}
		s++;
	}
	va_end(vl);
	return (len);
}
