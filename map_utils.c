#include "so_long.h"

char	get_corner_tile(char **map, t_data *data, int i, int j)
{
	if (i > 0 && (map[i -1][j] == '6' || map[i -1][j] == '4') \
	&& (j < data->map_width - 1 && (map[i][j + 1] == '3' \
	|| map[i][j + 1] == '4')))
		return ('B');
	else if (i > 0 && (map[i -1][j] == '2' || \
	map[i -1][j] == '0') && (j > 0 && \
	(map[i][j - 1] == '3' || map[i][j - 1] == '2')))
		return ('D');
	else if (i < data->map_height -1 && (map[i +1][j] == '0' || \
	map[i + 1][j] == '7') && (j > 0 && (map[i][j - 1] == '7' \
	|| map[i][j - 1] == '8')))
		return ('A');
	else if (i < data->map_height -1 && (map[i +1][j] == '6' || \
	map[i + 1][j] == '9') && (j < data->map_width - 1 && \
	(map[i][j + 1] == '8' || map[i][j + 1] == '9')))
		return ('1');
	else
		return ('5');
}

void	set_corner_tile(char ***map, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while ((*map)[++i])
	{
		j = -1;
		while ((*map)[i][++j])
		{
			if ((*map)[i][j] == '5')
				(*map)[i][j] = get_corner_tile((*map), data, i, j);
		}
	}
}

void	set_tile(char ***map, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while ((*map)[++i])
	{
		j = -1;
		while ((*map)[i][++j])
		{
			if ((*map)[i][j] == '1')
			{
				if ((i > 0 && i < data->map_height - 1) && ((*map)[i -1][j] >= \
				'A' && (*map)[i +1][j] >= 'A'))
					(*map)[i][j] = 'W';
				else if ((j > 0 && j < data->map_width - 1) && ((*map)[i][j -1] \
				>= 'A' && (*map)[i][j +1] >= 'A'))
					(*map)[i][j] = 'W';
			}
		}
	}
	set_wall_tile(map, data);
	set_corner_tile(map, data);
}

void	generate_cave(t_data *data, int i, int j)
{
	if (i > data->map_height / 4 && i < data->map_height -4 && \
	j > 0 && j < data->map_width - 1 && data->map_copy[i][j - 1] == '1' \
	&& data->map_copy[i][j + 1] == '1')
	{
		if ((data->map_copy[i + 1][j] == 'H' || \
		data->map_copy[i + 1][j] == '0') && data->map_copy[i - 1][j] == 'H')
		{
			mapcpy(data->map, data->map_copy);
			if (check_access(data, (int []){j - 1, i}, (int []){j + 1, i}))
			{
				data->map_copy[i][j] = '1';
				mapcpy(data->map_cave, data->map_copy);
				pg(data->map_cave, (int []){j, i - 1}, NULL, data);
				pg(data->map_copy, (int []){j, i + 1}, NULL, data);
				data->map_copy[i][j] = '-';
				data->map_cave[i][j] = '-';
			}
		}
	}
}

void	generate_trap(t_data *data, int i, int j)
{
	if (data->map[i][j] != '1' && data->map[i][j] != '#' && rand() % 100 < 5)
	{
		t_trap* newTrap = (t_trap*)malloc(sizeof(t_trap));
		if (!newTrap)
			{
				free_all(data);
				exit(1);
			}
		newTrap->x = i;
		newTrap->y = j;
		newTrap->frame = rand() %1001;
		newTrap->next = NULL;
		if (data->trap_list == NULL)
		{
			data->trap_list = newTrap;
		}
		else
		{
			t_trap* current = data->trap_list;
			while (current->next != NULL)
			{
				current = current->next;
			}
			current->next = newTrap;
		}
	}
}

void	map_setup(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map_copy[i][++j])
		{
			generate_trap(data, i, j);
			if (data->map_cave[i][j] == '0')
				data->map_cave[i][j] = 'H';
			if (data->map_copy[i][j] == '0')
			{
				data->map_copy[i][j] = 'H';
				if (!data->cave)
					generate_cave(data, i, j);
			}
		}
	}
	set_tile(&data->map_copy, data);
	set_tile(&data->map_cave, data);
}
