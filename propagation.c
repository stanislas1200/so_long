/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   propagation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:35:41 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/28 14:13:28 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_access_helper(char **map, int *end, t_data *data)
{
	int		x;
	int		y;

	y = data->stack->y;
	x = data->stack->x;
	pop(&data->stack);
	if (x == end[0] && y == end[1])
		data->cave = 1;
	if (map[y][x] == '1')
	{
		map[y][x] = '#';
		data->i = -2;
		while (++data->i < 2)
		{
			data->j = -2;
			while (++data->j < 2)
				if ((data->i == 0 || data->j == 0) && x + data->j >= 0 && \
				x + data->j < data->map_width && y + data->i >= 0 && \
				y + data->i < data->map_height && \
				map[y + data->i][x + data->j])
					push(&data->stack, x + data->j, y + data->i);
		}
	}
}

int	check_access(t_data	*data, int	*start, int	*end)
{
	data->stack = NULL;
	push(&data->stack, start[0], start[1]);
	while (data->stack && !data->cave)
		check_access_helper(data->map, end, data);
	cleanup_stack(data);
	return (data->cave);
}

void	pg_helper(char **map, int *start, int *end, t_data *data)
{
	int		x;
	int		y;

	x = data->stack->x;
	y = data->stack->y;
	pop(&data->stack);
	if (end && x == end[0] && y == end[1])
		data->reachable_end = 1;
	if (map[y][x] == '0' || map[y][x] == 'H' || map[y][x] == 'C'
	|| map[y][x] == 'E' || map[y][x] == 'P')
	{
		if (end)
			map[y][x] = 'X';
		else
			map[y][x] = '5';
		data->i = -2;
		while (++data->i < 2)
		{
			data->j = -2;
			while (++data->j < 2)
				if ((data->i == 0 || data->j == 0) && \
				map[data->i + start[1]][data->j + start[0]])
					push(&data->stack, x + data->j, y + data->i);
		}
	}
}

void	pg(char **map, int *start, int *end, t_data *data)
{
	data->stack = NULL;
	push(&data->stack, start[0], start[1]);
	while (data->stack)
		pg_helper(map, start, end, data);
	cleanup_stack(data);
}
