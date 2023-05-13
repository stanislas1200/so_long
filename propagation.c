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
/*dev*/
void print_map(t_data *data)
{
	int i = 0;
	int j = 0;
	while (data->map[i])
	{
		j = 0;
		printf("{");
		while (data->map[i][j])
		{
			// if (data->map_copy[i][j] == 'P')
			// 	printf("\x1b[1;35m%c\x1b[0m", data->map_copy[i][j]);
			// else if (data->map_copy[i][j] == 'E')
			// 	printf("\x1b[1;31m%c\x1b[0m", data->map_copy[i][j]);
			// else if (data->map_copy[i][j] == 'C' && data->map[i][j] == 'A')
			// 	printf("\x1b[1;36m%c\x1b[0m", data->map_copy[i][j]);
			// else if (data->map_copy[i][j] == 'C')
			// 	printf("\x1b[1;33m%c\x1b[0m", data->map_copy[i][j]);
			// else if (data->map[i][j] == 'A')
			// 	printf("\x1b[1;32m%c\x1b[0m", data->map_copy[i][j]);
			// else
				printf("\"%c\",", data->map_copy[i][j]);
			j++;
		}
		printf("}\n");
		i++;
	}
}
/*---*/
void propagate2(char **map, int *start, int *end, t_data *data)
{
	if (data->cave)
		return ;
	int	i;
	int	j;

	if (start[0] == end[0] && start[1] == end[1])
	{
		data->cave = 1;
		return ;
	}
	if (map[start[1]][start[0]] == '1')
	{
		i = -1;
		map[start[1]][start[0]] = '#';
		while (i < 2)
		{
			j = -1;
			while (j < 2)
			{
				if ((i == 0 || j == 0) && i + start[1] >= 0 && i + start[1] < data->map_height && j + start[0] >= 0 && j + start[0] < data->map_width && map[i + start[1]][j + start[0]])
					propagate2(map, (int []){j + start[0], i + start[1]}, end, data);
				j++;
			}
			i++;
		}
	}
}

int check_access(t_data *data, int *start, int *end)
{
	char **mapcpy;
	int i;
	int j;

	i = 0;
	mapcpy = malloc(sizeof(char *) * (data->map_height + 1));
	while (i < data->map_height)
	{
		j = 0;
		mapcpy[i] = malloc(sizeof(char) * (data->map_width + 1));
		while (j < data->map_width)
		{
			mapcpy[i][j] = data->map[i][j];
			j++;
		}
		mapcpy[i][j] = '\0';
		i++;
	}
	mapcpy[i] = NULL;
	propagate2(mapcpy, start, end, data);
	
	if (data->cave)
		return (1);
	return (0);
}
void propagate(char **map, int *start, int *end, t_data *data, t_propagation_data *parent)
{
	int	i;
	int	j;

	/*dev*/
	t_propagation_data	*new_data = malloc(sizeof(t_propagation_data));

	new_data->x = start[0];
	new_data->y = start[1];
	new_data->parent = parent;
	/*---*/
	if (end && start[0] == end[0] && start[1] == end[1])
	{
		data->reachable_end = 1;
		/*dev*/
		t_propagation_data	*current = new_data;
		while (current->parent)
		{
			map[current->y][current->x] = 'A';
			current = current->parent;
		}
		if (data->printed == 0)
		{
			// print_map(data);
			data->printed = 1;
		}
		free(new_data);
		/*---*/
		return ;
	}
	if (map[start[1]][start[0]] == '0' || map[start[1]][start[0]] == 'H' || map[start[1]][start[0]] == 'C' || map[start[1]][start[0]] == 'E' || map[start[1]][start[0]] == 'P')
	{
		i = -1;
		if (end)
			map[start[1]][start[0]] = 'X';
		else 
			map[start[1]][start[0]] = '5';
		while (i < 2)
		{
			j = -1;
			while (j < 2)
			{
				if ((i == 0 || j == 0) && map[i + start[1]][j + start[0]])
				{
					propagate(map, (int []){j + start[0], i + start[1]}, end, data, new_data);
				}
				j++;
			}
			i++;
		}
	}
	free(new_data);
	// /*---*/
	// print_map(data);
	// /*---*/
}
