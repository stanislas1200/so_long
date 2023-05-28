
#include "so_long.h"

void	end(void)
{
	printf("You lose!\n");
	system("leaks so_long");
	exit(0);
}

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
