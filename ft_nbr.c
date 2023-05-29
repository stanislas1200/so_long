/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:22:57 by sgodin            #+#    #+#             */
/*   Updated: 2022/11/02 15:57:56 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "ft_printf.h"

void	ft_putnbr2(int nb)
{
	char	c;

	if (nb == 0)
		return ;
	c = '0' + nb % 10;
	ft_putnbr2(nb / 10);
	write (1, &c, 1);
}

int	ft_putnbr(int nb)
{
	int	len;

	len = ft_nbrlen(nb);
	if (nb == -2147483648)
	{
		write (1, "-2147483648", 11);
		return (len);
	}
	if (nb == 0)
	{
		write (1, "0", 1);
		return (len);
	}
	if (nb < 0)
	{
		write (1, "-", 1);
		nb = -nb;
	}
	ft_putnbr2 (nb);
	return (len);
}

int	ft_nbrlen(int nb)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
	{
		return (11);
	}
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}
