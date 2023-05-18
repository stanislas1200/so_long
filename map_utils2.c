#include "so_long.h"

/**
 * Check for common errors in the game map.
 *
 * This function checks if the map contains exactly one player, one exit,
 * and at least one collectible item. If any of these conditions are not met,
 * an error message is printed and the function returns 0. Otherwise, it returns 1.
 *
 * @param data A pointer to a t_data struct that contains the game data.
 * @return 1 if no errors are found, 0 otherwise.
 */
int	check_map_tiles(t_data *data, int i, int j)
{
	data->player_possition = malloc(sizeof(int) * 2);
	data->exit_possition = malloc(sizeof(int) * 2);
	if (!data->player_possition || !data->exit_possition)
	{
		perror("\x1b[1;31mError\x1b[0m");
		return (0);
	}
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
			if (!check_map_tiles_helper(data, i, j))
				break ;
		if (check_line_char(data->map[i], i, 0) == 0)
			return (0);
	}
	if (!check_line_char(data->map[i - 1], i - 1, 1))
		return (0);
	if (!check_common_errors(data))
		return (0);
	pg(data->map, data->player_possition, data->exit_possition, data);
	check_collectible_access(data);
	return (1);
}

void	mapcpy(char **dest, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			dest[i][j] = map[i][j];
	}
}

char	get_wall_tile_helper(t_data *data, char **map, int i, int j)
{
	if (j > 0 && (map[i][j -1] < '0' || map[i][j -1] > '9'))
		return ('7');
	else if (j < data->map_width -1 && \
	(map[i][j +1] < '0' || map[i][j +1] > '9'))
		return ('9');
	else
		return ('8');
}

char	get_wall_tile(t_data *data, char **map, int i, int j)
{
	if (i > 0 && ((map[i -1][j] < '0' || map[i -1][j] > '9')))
	{
		if (j > 0 && (map[i][j -1] < '0' || map[i][j -1] > '9'))
			return ('2');
		else if (j < data->map_width -1 && \
		(map[i][j +1] < '0' || map[i][j +1] > '9'))
			return ('4');
		else
			return ('3');
	}
	else if (i < data->map_height -1 && \
	(map[i +1][j] < '0' || map[i +1][j] > '9'))
	{
		return (get_wall_tile_helper(data, map, i, j));
	}
	else if (j > 0 && (map[i][j -1] < '0' || map[i][j -1] > '9'))
		return ('0');
	else if (j < data->map_width -1 && \
	(map[i][j +1] < '0' || map[i][j +1] > '9'))
		return ('6');
	else
		return ('5');
}

void	set_wall_tile(char ***map, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while ((*map)[++i])
	{
		j = -1;
		while ((*map)[i][++j])
			if ((*map)[i][j] == '1')
				(*map)[i][j] = get_wall_tile(data, (*map), i, j);
	}
}
