#include "so_long.h"

void print_map(char **map)
{
	int i = 0;
	int j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'A')
				printf("\x1b[32m%c\x1b[0m", map[i][j]);
			else
				printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void propagate(char **map, int *start, int *end, t_data *data, t_propagation_data *parent)
{
	t_propagation_data *new_data = malloc(sizeof(t_propagation_data));

	new_data->x = start[0];
	new_data->y = start[1];
	new_data->parent = parent;

	if (start[0] == end[0] && start[1] == end[1])
	{
		data->reachable_end = 1;
		t_propagation_data *current = new_data;
		while (current->parent)
		{
			map[current->y][current->x] = 'A';
			current = current->parent;
		}
		if (data->printed == 0){
			print_map(map);
			data->printed = 1;
			}
		free(new_data);
		return ;
	}
	if (map[start[1]][start[0]] == '0' || map[start[1]][start[0]] == 'C' || map[start[1]][start[0]] == 'E' || map[start[1]][start[0]] == 'P')
	{
		int i = -1;
		map[start[1]][start[0]] = 'x';
		while (i < 2)
		{
			int j = -1;
			while (j < 2)
			{
				if ((i == 0 || j == 0) && map[i + start[1]][j + start[0]])
				{
					propagate (map, (int[]){j + start[0], i + start[1]}, end, data, new_data);
				}
				j++;
			}
			i++;
		}
	}
	free(new_data);
}

