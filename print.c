/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:46:45 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/29 16:00:46 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len = 1;
	while (nbr != 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	int		i;

	i = get_len(nbr);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (nbr == 0)
		str[i] = '0';
	while (nbr != 0)
	{
		str[i--] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (str);
}

void	end(t_data *data, int code)
{
	if (!code)
		ft_printf("\x1b[1;31mGAME OVER\x1b[0m: Killed by a Trap!\n");
	if (code == 2)
		ft_printf("\x1b[1;31mGAME OVER\x1b[0m: Killed by a Enemy!\n");
	else if (code == 1)
		ft_printf("\x1b[1;32mYou Win\x1b[0m: With %d moves!\n", \
		data->player_move_count);
	free_all(data);
	exit(0);
}

void	print_on_screen(t_data *data)
{
	int		i;
	char	*move;
	char	*nbr;

	move = ft_itoa(data->player_move_count);
	nbr = ft_itoa(data->collectible_nbr);
	if (!data->design_mode)
	{
		i = -1;
		while (++i < 4)
			mlx_put_image_to_window(data->mlx, data->win, \
				get_tile(data, data->ptr[0][i]), i * 50, 0);
	}
	mlx_string_put(data->mlx, data->win, 5, 10, 136, "Move Count: ");
	mlx_string_put(data->mlx, data->win, 160, \
	10, 136, move);
	mlx_string_put(data->mlx, data->win, 5, 25, 136, "Collected left: ");
	mlx_string_put(data->mlx, data->win, 160, \
	25, 136, nbr);
	free(move);
	free(nbr);
}
