
#include "so_long.h"

void	draw_map_helper(t_data *data)
{
	int		i;
	int		j;
	void	*img;

	i = -1;
	while (data->ptr[++i])
	{
		j = -1;
		while (data->ptr[i][++j])
		{
			if (data->ptr[i][j] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->arr[14], \
						j * 50, i * 50);
			img = get_tile(data, data->ptr[i][j]);
			if (!img)
				mlx_put_image_to_window(data->mlx, data->win, \
				data->img->unknown_tile, j * 50, i * 50);
			else
				mlx_put_image_to_window(data->mlx, data->win, img, \
				j * 50, i * 50);
		}
	}
}

void	draw_player_chunck(t_data *data, int x, int y)
{
	if (x > 0 && x < data->map_width - 21)
		x = 10;
	else if (x > data->map_width - 22)
		x = data->player_possition[0] - data->map_width + 20;
	else
		x = data->player_possition[0];
	if (y > 0 && y < data->map_height - 11)
		y = 5;
	else if (y > data->map_height - 12)
		y = data->player_possition[1] - data->map_height + 10;
	else
		y = data->player_possition[1];
	mlx_put_image_to_window(data->mlx, data->win, data->img->\
	player[data->direction][(data->time / 10) % 4], \
	x * 50, y * 50);
}

void	draw_chunck_helper(t_data *data, int x, int y)
{
	int		i;
	int		j;
	void	*img;

	img = NULL;
	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 20)
		{
			img = get_tile(data, data->ptr[i + y][j + x]);
			if (!img)
				mlx_put_image_to_window(data->mlx, data->win, \
				data->img->unknown_tile, j * 50, i * 50);
			else
				mlx_put_image_to_window(data->mlx, data->win, img, \
				j * 50, i * 50);
		}
	}
}

void	draw_chunck(t_data *data)
{
	int		x;
	int		y;

	y = data->player_possition[1] - 5;
	x = data->player_possition[0] - 10;
	if (-1 + y < 0)
		y = 0;
	if (-1 + x < 0)
		x = 0;
	if (10 + y > data->map_height)
		y = data->map_height - 10;
	if (20 + x > data->map_width)
		x = data->map_width - 20;
	draw_chunck_helper(data, x, y);
	draw_player_chunck(data, x, y);
}

void	draw_map(t_data *data)
{
	if (data->design_mode)
		draw_chunck(data);
	else
		draw_map_helper(data);
	print_on_screen(data);
}
