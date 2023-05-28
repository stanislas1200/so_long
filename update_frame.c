
#include "so_long.h"

void	update_portal_helper(t_data *data)
{
	if (!data->cave && \
	data->map_copy[data->exit_possition[1]][data->exit_possition[0]] != '5' \
	&& !data->design_mode)
	{
		mlx_put_image_to_window(data->mlx, data->win, get_tile(data, \
		data->ptr[data->exit_possition[1]][data->exit_possition[0]]), \
		data->exit_possition[0] * 50, data->exit_possition[1] * 50);
		if (data->collectible_nbr == 0)
			mlx_put_image_to_window(data->mlx, data->win, \
			data->img->exit_on[(data->time / 10) % 4], \
			data->exit_possition[0] * 50, data->exit_possition[1] * 50);
		else
			mlx_put_image_to_window(data->mlx, data->win, data->img->exit_tile, \
			data->exit_possition[0] * 50, data->exit_possition[1] * 50);
	}
}

void	update_portal(t_data *data)
{
	if (data->cave && \
	data->map_cave[data->exit_possition[1]][data->exit_possition[0]] != '5' \
	&& !data->design_mode)
	{
		mlx_put_image_to_window(data->mlx, data->win, get_tile(data, \
		data->ptr[data->exit_possition[1]][data->exit_possition[0]]), \
		data->exit_possition[0] * 50, data->exit_possition[1] * 50);
		if (data->collectible_nbr == 0)
			mlx_put_image_to_window(data->mlx, data->win, \
			data->img->exit_on[(data->time / 10) % 4], \
			data->exit_possition[0] * 50, data->exit_possition[1] * 50);
		else
			mlx_put_image_to_window(data->mlx, data->win, data->img->exit_tile, \
			data->exit_possition[0] * 50, data->exit_possition[1] * 50);
	}
	else
		update_portal_helper(data);
}

void	update_player_frame(t_data *data)
{
	if (data->design_mode)
	{
		if (data->player_possition[0] >= 10 && data->player_possition[1] >= 5 \
		&& data->player_possition[0] < data->map_width - 10 \
		&& data->player_possition[1] < data->map_height - 5)
			mlx_put_image_to_window(data->mlx, data->win, data->img->\
			player[data->direction][(data->time / 10) % 4], \
			10 * 50, 5 * 50);
	}
	else
		mlx_put_image_to_window(data->mlx, data->win, data->img->\
		player[data->direction][(data->time / 10) % 4], \
		data->player_possition[0] * 50, data->player_possition[1] * 50);
}

int	update_frame(t_data *data)
{
	if (data->time >= 1000)
		data->time = 0;
	if (data->design_mode)
	{
		if (data->player_possition[0] >= 10 && data->player_possition[1] >= 5 \
		&& data->player_possition[0] < data->map_width - 10 \
		&& data->player_possition[1] < data->map_height - 5)
			mlx_put_image_to_window(data->mlx, data->win, get_tile(data, \
			data->ptr[data->exit_possition[1]][data->exit_possition[0]]), \
			10 * 50, 5 * 50);
	}
	else
	{
		mlx_put_image_to_window(data->mlx, data->win, get_tile(data, \
		data->ptr[data->player_possition[1]][data->player_possition[0]]), \
		data->player_possition[0] * 50, data->player_possition[1] * 50);
	}
	update_portal(data);
	update_trap(data);
	update_enemy(data);
	update_player_frame(data);
	data->time++;
	return (0);
}
