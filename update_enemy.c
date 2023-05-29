/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:46:21 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/29 13:28:46 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_enemy(t_data *data, t_enemy *enemy)
{
	int	*pos;

	pos = (int []){enemy->x, enemy->y};
	if (enemy->direction == 0)
		pos[1] -= 1;
	else if (enemy->direction == 1)
		pos[1] += 1;
	else if (enemy->direction == 2)
		pos[0] += 1;
	else if (enemy->direction == 3)
		pos[0] -= 1;
	if (data->map[pos[1]][pos[0]] == '1' || data->map[pos[1]][pos[0]] == '#')
	{
		enemy->direction = (enemy->direction + rand()) % 4;
		return ;
	}
	enemy->x = pos[0];
	enemy->y = pos[1];
}

void	update_enemy_frame_chelper(t_data *data, t_enemy *current)
{
	mlx_put_image_to_window(data->mlx, data->win, \
	get_tile(data, data->ptr[current->y - 1][current->x]), \
	data->j * 50, (data->i - 1) * 50);
	mlx_put_image_to_window(data->mlx, data->win, \
	get_tile(data, data->ptr[current->y + 1][current->x]), \
	data->j * 50, (data->i + 1) * 50);
	mlx_put_image_to_window(data->mlx, data->win, \
	get_tile(data, data->ptr[current->y][current->x]), \
	data->j * 50, data->i * 50);
	mlx_put_image_to_window(data->mlx, data->win, \
	get_tile(data, data->ptr[current->y][current->x + 1]), \
	(data->j + 1) * 50, data->i * 50);
	mlx_put_image_to_window(data->mlx, data->win, \
	get_tile(data, data->ptr[current->y][current->x - 1]), \
	(data->j - 1) * 50, data->i * 50);
	if ((current->frame) % 80 == 0)
		move_enemy(data, current);
	mlx_put_image_to_window(data->mlx, data->win, data->\
	img->enemy[current->direction][(current->frame / \
	10) % 4], \
	data->j * 50, data->i * 50);
}

void	update_enemy_frame_chunck(t_data *data, t_enemy *current)
{
	int	x;
	int	y;

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
	data->i = -1;
	while (++data->i < 10)
	{
		data->j = -1;
		while (++data->j < 20)
		{
			if (current->x == data->j + x && current->y == data->i + y)
				update_enemy_frame_chelper(data, current);
		}
	}
}

void	update_enemy_frame(t_data *data, t_enemy *current)
{
	if (data->cave && data->map_cave[current->y][current->x] != '5')
	{
		mlx_put_image_to_window(data->mlx, data->win, \
		get_tile(data, data->ptr[current->y][current->x]), \
		current->x * 50, current->y * 50);
		if ((current->frame) % 10 == 0)
			move_enemy(data, current);
		mlx_put_image_to_window(data->mlx, data->win, \
		data->img->enemy[current->direction][(current->frame / 10) % 4], \
		current->x * 50, current->y * 50);
	}
	else if (!data->cave && data->map_copy[current->y][current->x] != '5')
	{
		mlx_put_image_to_window(data->mlx, data->win, \
		get_tile(data, data->ptr[current->y][current->x]), \
		current->x * 50, current->y * 50);
		if ((current->frame) % 50 == 0)
			move_enemy(data, current);
		mlx_put_image_to_window(data->mlx, data->win, \
		data->img->enemy[current->direction][(current->frame / 10) % 4], \
		current->x * 50, current->y * 50);
	}
}

void	update_enemy(t_data *data)
{
	t_enemy	*current;

	current = data->enemy_list;
	while (current != NULL)
	{
		current->frame = (current->frame + 1) % 1001;
		if (current->x == data->player_possition[0] \
		&& current->y == data->player_possition[1])
		{
			data->player_hp--;
			if (data->player_hp <= 0)
				end(data, 2);
		}
		if (data->design_mode)
			update_enemy_frame_chunck(data, current);
		else
			update_enemy_frame(data, current);
		current = current->next;
	}
}
