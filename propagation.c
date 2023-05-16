/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   propagation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:35:41 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/10 15:20:39 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	pg2(char **map, int *start, int *end, t_data *data)
{
	int	i;
	int	j;

	if (start[0] == end[0] && start[1] == end[1])
	{
		data->cave = 1;
		return ;
	}
	if (map[start[1]][start[0]] == '1')
	{
		i = -2;
		map[start[1]][start[0]] = '#';
		while (++i < 2)
		{
			j = -2;
			while (++j < 2)
				if ((i == 0 || j == 0) && i + start[1] >= 0 && \
				i + start[1] < data->map_height && j + start[0] >= 0 && \
				j + start[0] < data->map_width && \
				map[i + start[1]][j + start[0]])
					pg2(map, (int []){j + start[0], i + start[1]}, end, data);
		}
	}
}

int	check_access(t_data *data, int *start, int *end)
{
	pg2(data->map, start, end, data);
	if (data->cave)
		return (1);
	return (0);
}

void	pg(char **map, int *start, int *end, t_data *data)
{
	int	i;
	int	j;

	if (end && start[0] == end[0] && start[1] == end[1])
	{
		data->reachable_end = 1;
		return ;
	}
	if (map[start[1]][start[0]] == '0' || map[start[1]][start[0]] == 'H' || \
	map[start[1]][start[0]] == 'C' || \
	map[start[1]][start[0]] == 'E' || map[start[1]][start[0]] == 'P')
	{
		i = -2;
		if (end)
			map[start[1]][start[0]] = 'X';
		else
			map[start[1]][start[0]] = '5';
		while (++i < 2)
		{
			j = -2;
			while (++j < 2)
				if ((i == 0 || j == 0) && map[i + start[1]][j + start[0]])
					pg(map, (int []){j + start[0], i + start[1]}, end, data);
		}
	}
}
