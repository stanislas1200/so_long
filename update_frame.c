/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:46:17 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/30 16:29:34 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_gui(t_data *data)
{
	int	i;

	mlx_put_image_to_window(data->mlx, data->win, data->img->gui[0], \
	(data->map_width - 2) * 50, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->img->gui[1], \
	(data->map_width - 1) * 50, 0);
	i = -1;
	while (++i < data->player_hp)
		mlx_put_image_to_window(data->mlx, data->win, data->img->bar[0], \
		(data->map_width - 1) * 50 + i * 4, 0);
	i = -1;
	while (++i < (data->time / 100) % 8)
		mlx_put_image_to_window(data->mlx, data->win, data->img->bar[1], \
		(data->map_width - 1) * 50 + i * 4, 0);
	if (data->player_hp < data->player_max_hp && data->time == 899)
		data->player_hp++;
}

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
	update_gui(data);
	data->time++;
	return (0);
}
