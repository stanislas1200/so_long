/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:47:24 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/29 12:59:11 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player2(int keycode, t_data *data, char **map)
{
	int	x;
	int	y;

	x = data->player_possition[0];
	y = data->player_possition[1];
	if (keycode == 12 || keycode == 123)
	{
		data->direction = 2;
		if (map[y][x - 1] != '1' && map[y][x - 1] != '#')
			data->player_possition[0]--;
	}
	else if (keycode == 2 || keycode == 124)
	{
		data->direction = 3;
		if (map[y][x + 1] != '1' && map[y][x + 1] != '#')
			data->player_possition[0]++;
	}
}

void	move_player(int keycode, t_data *data, char **map)
{
	int	x;
	int	y;

	x = data->player_possition[0];
	y = data->player_possition[1];
	if (keycode == 13 || keycode == 126)
	{
		data->direction = 0;
		if (map[y - 1][x] != '1' && map[y - 1][x] != '#')
			data->player_possition[1]--;
	}
	else if (keycode == 1 || keycode == 125)
	{
		data->direction = 1;
		if (map[y + 1][x] != '1' && map[y + 1][x] != '#')
			data->player_possition[1]++;
	}
	else
		move_player2(keycode, data, map);
	if (keycode == 2 || keycode == 12 || keycode == 1 || keycode == 13 \
	|| keycode == 124 || keycode == 123 || keycode == 125 || keycode == 126)
		data->player_move_count++;
}

void	exit_tile_check(t_data *data)
{
	if (data->ptr[data->player_possition[1]][data->player_possition[0]] \
	== 'E' && data->collectible_nbr == 0)
		end(data, 1);
}

void	do_tile_action(t_data *data)
{
	if (data->ptr[data->player_possition[1]][data->player_possition[0]] == 'C')
	{
		data->ptr[data->player_possition[1]][data->player_possition[0]] = 'H';
		data->collectible_nbr--;
	}
	else if (data->ptr[data->player_possition[1]][data->player_possition[0]] \
	== '-')
	{
		if (data->cave)
		{
			data->ptr = data->map_copy;
			data->arr = data->img->outside_tiles;
			data->cave = 0;
			data->player_possition[1] = data->player_possition[1] - 1;
		}
		else
		{
			data->ptr = data->map_cave;
			data->arr = data->img->inside_tiles;
			data->cave = 1;
			data->player_possition[1] = data->player_possition[1] + 1;
		}
		draw_map(data);
	}
	exit_tile_check(data);
}

void	check_trap_collision(t_data *data)
{
	t_trap	*current;

	current = data->trap_list;
	while (current != NULL)
	{
		if (current->x == data->player_possition[0]
			&& current->y == data->player_possition[1])
		{
			if ((current->frame / 10) % 9 == 7)
				end(data, 0);
			else
				break ;
		}
		current = current->next;
	}
}
