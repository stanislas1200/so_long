/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:46:39 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/30 16:33:46 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*get_tile_helper(t_data *data, char tile)
{
	if (tile == 'A')
		return (data->arr[11]);
	else if (tile == 'B')
		return (data->arr[12]);
	else if (tile == 'D')
		return (data->arr[13]);
	else if (tile == 'H' || tile == 'P')
		return (data->arr[14]);
	else if (tile == 'C')
	{
		if ((data->time / 10) % 2)
			return (data->arr[15]);
		return (data->arr[16]);
	}
	else if (tile == 'E')
	{
		if (data->collectible_nbr == 0)
			return (data->img->exit_on[(data->time / 10) % 4]);
		else
			return (data->img->exit_tile);
	}
	else if (tile == '-')
		return (data->arr[17]);
	else
		return (data->img->unknown_tile);
}

void	*get_tile(t_data *data, char tile)
{
	if (tile == '2')
		return (data->arr[0]);
	else if (tile == '3')
		return (data->arr[1]);
	else if (tile == '4')
		return (data->arr[2]);
	else if (tile == '0')
		return (data->arr[3]);
	else if (tile == '5')
		return (data->arr[4]);
	else if (tile == '6')
		return (data->arr[5]);
	else if (tile == '7')
		return (data->arr[6]);
	else if (tile == '8')
		return (data->arr[7]);
	else if (tile == '9')
		return (data->arr[8]);
	else if (tile == 'W')
		return (data->arr[9]);
	else if (tile == '1')
		return (data->arr[10]);
	else
		return (get_tile_helper(data, tile));
}

int	setting_mlx(t_data *data)
{
	if (data->map_height > 28 || data->map_width > 50)
		data->design_mode = 1;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	if (data->design_mode)
	{
		data->win = mlx_new_window(data->mlx, 1000, 500, \
		"The Mysterious Firefly Cave");
		if (!data->win)
			return (0);
	}
	else
	{
		data->win = mlx_new_window(data->mlx, 50 * data->map_width, 50 * \
		data->map_height, "The Mysterious Firefly Cave");
		if (!data->win)
			return (0);
	}
	return (1);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 53)
		end(data, 3);
	mlx_put_image_to_window(data->mlx, data->win, \
	get_tile(data,
			data->ptr[data->player_possition[1]][data->player_possition[0]]),
		data->player_possition[0] * 50, data->player_possition[1] * 50);
	move_player(keycode, data, data->map);
	do_tile_action(data);
	if (data->design_mode)
		draw_map(data);
	else
		mlx_put_image_to_window(data->mlx, data->win, data->img->\
		player[data->direction][(data->time / 10) % 4], \
		data->player_possition[0] * 50, data->player_possition[1] * 50);
	check_trap_collision(data);
	print_on_screen(data);
	return (0);
}

void	start_game(t_data *data)
{
	data->player_hp = data->player_max_hp;
	map_setup(data);
	if (data->map_copy[data->player_possition[1]][data->player_possition[0]] \
	== 'P')
		data->cave = 0;
	data->img = malloc(sizeof(t_img));
	if (!data->img || !setting_mlx(data))
		return ;
	load_image(data);
	if (data->cave)
	{
		data->ptr = data->map_cave;
		data->arr = data->img->inside_tiles;
	}
	else
	{
		data->ptr = data->map_copy;
		data->arr = data->img->outside_tiles;
	}
	draw_map(data);
	mlx_hook(data->win, 2, 0, &key_press, data);
	mlx_loop_hook(data->mlx, update_frame, data);
	mlx_loop(data->mlx);
}
