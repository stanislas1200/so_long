/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_trap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:46:11 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/29 12:59:21 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_trap_frame_chelper(t_data *data, t_trap *current)
{
	mlx_put_image_to_window(data->mlx, data->win, \
	get_tile(data, data->ptr[current->y][current->x]), \
	data->j * 50, data->i * 50);
	mlx_put_image_to_window(data->mlx, data->win, \
	data->img->trap[(current->frame / 10) % 9], \
	data->j * 50, data->i * 50);
}

void	update_trap_frame_chunck(t_data *data, t_trap *current)
{
	int	y;
	int	x;

	x = data->player_possition[0] - 10;
	y = data->player_possition[1] - 5;
	if (-1 + y < 0)
		y = 0;
	if (-1 + x < 0)
		x = 0;
	if (10 + y > data->map_height)
		y = data->map_height - 10;
	if (20 + x > data->map_width)
		x = data->map_width - 20;
	data->i = -1;
	while (++data->i < 10)
	{
		data->j = -1;
		while (++data->j < 20)
		{
			if (current->x == data->j + x && current->y == data->i + y)
				update_trap_frame_chelper(data, current);
		}
	}
}

void	update_trap_frame(t_data *data, t_trap *current)
{
	if (data->cave && data->map_cave[current->y][current->x] != '5')
	{
		mlx_put_image_to_window(data->mlx, data->win, \
		get_tile(data, data->ptr[current->y][current->x]), \
		current->x * 50, current->y * 50);
		mlx_put_image_to_window(data->mlx, data->win, \
		data->img->trap[(current->frame / 10) % 9], \
		current->x * 50, current->y * 50);
	}
	else if (!data->cave && data->map_copy[current->y][current->x] != '5')
	{
		mlx_put_image_to_window(data->mlx, data->win, \
		get_tile(data, data->ptr[current->y][current->x]), \
		current->x * 50, current->y * 50);
		mlx_put_image_to_window(data->mlx, data->win, \
		data->img->trap[(current->frame / 10) % 9], \
		current->x * 50, current->y * 50);
	}
}

void	update_trap(t_data *data)
{
	t_trap	*current;

	current = data->trap_list;
	while (current != NULL)
	{
		current->frame = (current->frame + 1) % 1001;
		if (current->x == data->player_possition[0] \
		&& current->y == data->player_possition[1])
			if ((current->frame / 10) % 9 == 7)
				end(data, 0);
		if (data->design_mode)
			update_trap_frame_chunck(data, current);
		else
			update_trap_frame(data, current);
		current = current->next;
	}
}
