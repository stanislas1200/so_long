#include "so_long.h"

char **new_mapcpy(char **map, int height, int width)
{
	char **new_map;
	int i;
	int j;

	i = -1;
	if (!map)
		return (NULL);
	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	while (++i < height)
	{
		new_map[i] = malloc(sizeof(char) * (width + 1));
		if (!new_map[i])
		{
			while (--i >= 0)
				free(new_map[i]);
			free(new_map);
			return (NULL);
		}
		j = -1;
		while (++j < width)
			new_map[i][j] = map[i][j];
		new_map[i][j] = '\0';
	}
	new_map[i] = NULL;
	return (new_map);
}

int	check_line_char(char *line, int line_nbr, int last_line)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen(line);
	while (line && line[++i])
	{
		
		if (line[i] != '1' && line[i] != '0' && line[i] != 'C' && line[i] != 'E' && line[i] != 'P')
		{
			
			printf("\x1b[1;31mError\x1b[0m: Map line\x1b[1;35m%d:%d\x1b[0m contains invalid characters\n", line_nbr + 1, i + 1);
			return (0);
		}
		if (line_nbr == 0 && line[i] != '1')
		{
			printf("\x1b[1;31mError\x1b[0m: Map line\x1b[1;35m%d:%d\x1b[0m is not closed\n", line_nbr + 1, i + 1);
			return (0);
		}
		if ((i == 0 || i == len - 1) && line[i] != '1')
		{
			printf("\x1b[1;31mError\x1b[0m: Map line\x1b[1;35m%d:%d\x1b[0m is not closed\n", line_nbr + 1, i + 1);
			return (0);
		}
		if (last_line && line[i] != '1')
		{
			printf("\x1b[1;31mError\x1b[0m: Map line\x1b[1;35m%d:%d\x1b[0m is not closed\n", line_nbr + 1, i + 1);
			return (0);
		}

		
	}
	return (1);
}

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
int check_common_errors(t_data *data) {
	if (data->player_nbr > 1) {
		printf("\x1b[1;31mError\x1b[0m: Too many player on the map\n");
		return (0);
	}
	if (data->exit_nbr > 1) {
		printf("\x1b[1;31mError\x1b[0m: Too many exit on the map\n");
		return (0);
	}
	if (data->player_nbr < 1) {
		printf("\x1b[1;31mError\x1b[0m: No player on the map\n");
		return (0);
	}
	if (data->exit_nbr < 1) {
		printf("\x1b[1;31mError\x1b[0m: No exit on the map\n");
		return (0);
	}
	if (data->collectible_nbr == 0) {
		printf("\x1b[1;31mError\x1b[0m: No collectible on the map\n");
		return (0);
	}
	return (1);
}


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
int check_map_tiles(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->player_possition = malloc(sizeof(int) * 2);
	data->exit_possition = malloc(sizeof(int) * 2);
	if (!data->player_possition || !data->exit_possition)
	{
		perror("\x1b[1;31mError\x1b[0m");
		return (0);
	}
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'P')
			{
				data->player_nbr++;
				data->player_possition[0] = j;
				data->player_possition[1] = i;
			}
			else if (data->map[i][j] == 'E')
			{
				data->exit_nbr++;
				data->exit_possition[0] = j;
				data->exit_possition[1] = i;
			}
			else if (data->map[i][j] == 'C')
				data->collectible_nbr++;
			if (data->player_nbr > 1)
				break ;
			if (data->exit_nbr > 1)
				break ;
			j++;
		}
		if (check_line_char(data->map[i], i, 0) == 0)
			return (0);
		i++;
	}
	if (check_line_char(data->map[i - 1], i - 1, 1) == 0)
		return (0);
	if (!check_common_errors(data))
		return (0);
	pg(data->map, data->player_possition, data->exit_possition, data);
	if (!data->reachable_end)
	{
		printf("\x1b[1;31mError\x1b[0m: No acces to exit\n");
		return (0);
	}
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'C')
			{
				printf("\x1b[1;31mError\x1b[0m: No acces to \x1b[33mCollectible\x1b[0m line \x1b[1;35m%d:%d\x1b[0m\n", i + 1, j + 1);
				data->reachable_end = 0;
			}
		}
	}
	return (1);
}

void mapcpy(char **dest, char **map)
{
	int i;
	int j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			dest[i][j] = map[i][j];
	}
}

char get_wall_tile(t_data *data,char **map, int i, int j) {
    char tile = map[i][j];
    
    if (tile == '1') {
        // Check neighboring tiles to determine wall tile
        if (i > 0 && ((map[i-1][j] < '0' || map[i-1][j] > '9'))) { // Check top tile
            if (j > 0 && (map[i][j-1] < '0' || map[i][j-1] > '9')) { // Check left tile
                tile = '2';
            } else if (j < data->map_width - 1 && (map[i][j+1] < '0' || map[i][j+1] > '9')) { // Check right tile
                tile = '4';
            } else {
                tile = '3';
            }
        }
        else if (i < data->map_height - 1 && (map[i+1][j] < '0' || map[i+1][j] > '9')) { // Check bottom tile
            if (j > 0 && (map[i][j-1] < '0' || map[i][j-1] > '9')) { // Check left tile
                tile = '7';
            } else if (j < data->map_width - 1 && (map[i][j+1] < '0' || map[i][j+1] > '9')) { // Check right tile
                tile = '9';
            } else {
                tile = '8';
            }
        }
        else if (j > 0 && (map[i][j-1] < '0' || map[i][j-1] > '9')) { // Check left tile
            tile = '0';
        }
        else if (j < data->map_width - 1 && (map[i][j+1] < '0' || map[i][j+1] > '9')) { // Check right tile
            tile = '6';
        }
        else tile = '5';
    }
    return tile;
}

void	set_tile(char ***map, t_data *data)
{
    int i = -1;
    int j;
    while ((*map)[++i])
    {
        j = -1;
        while ((*map)[i][++j])
        {
            if ((*map)[i][j] == '1') {
                if ((i > 0 && i < 9) && ((*map)[i-1][j] >= 'A' && (*map)[i+1][j] >= 'A'))
                    (*map)[i][j] = 'W';
                else if ((j > 0 && j < 19) && ((*map)[i][j-1] >= 'A' && (*map)[i][j+1] >= 'A'))
                    (*map)[i][j] = 'W';
            }
        }
    }
    i = -1;
    while ((*map)[++i])
    {
        j = -1;
        while ((*map)[i][++j])
            (*map)[i][j] = get_wall_tile(data, (*map), i, j);
    }

    i = -1;
    while ((*map)[++i])
    {
        j = -1;
        while ((*map)[i][++j])
        {
            if ((*map)[i][j] == '5')
            {
                if (i > 0 && ((*map)[i - 1][j] == '6' || (*map)[i - 1][j] == '4') && (j < data->map_width - 1 && ((*map)[i][j + 1] == '3' || (*map)[i][j + 1] == '4')))
                    (*map)[i][j] = 'B';
                else if (i > 0 && ((*map)[i - 1][j] == '2' || (*map)[i - 1][j] == '0') && (j > 0 && ((*map)[i][j - 1] == '3' || (*map)[i][j - 1] == '2')))
                    (*map)[i][j] = 'D';
                else if (i < data->map_height - 1 && ((*map)[i + 1][j] == '0' || (*map)[i + 1][j] == '7') && (j > 0 && ((*map)[i][j - 1] == '7' || (*map)[i][j - 1] == '8')))
                    (*map)[i][j] = 'A';
                else if (i < data->map_height - 1 && ((*map)[i + 1][j] == '6' || (*map)[i + 1][j] == '9') && (j < data->map_width - 1 && ((*map)[i][j + 1] == '8' || (*map)[i][j + 1] == '9')))
                    (*map)[i][j] = '1';
            }
        }
    }
}

void map_setup(t_data *data)
{
	// EPCX

	// 234
	// 056
	// 789 W

	// 1A
	// BD
	int i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1; // Check pg and checking function to merge
		while (data->map_copy[i][++j])
		{
			if (data->map_cave[i][j] == '0')
				data->map_cave[i][j] = 'H';
			if(data->map_copy[i][j] == '0')
			{
				data->map_copy[i][j] = 'H';
				if (!data->cave && i > data->map_height/3 && i < data->map_height/3 * 2 &&  j > 0 && j < data->map_width - 1 && data->map_copy[i][j - 1] == '1' && data->map_copy[i][j + 1] == '1')
					if ((data->map_copy[i + 1][j] == 'H' || data->map_copy[i+1][j] == '0') && data->map_copy[i - 1][j] == 'H')
					{
						mapcpy(data->map, data->map_copy);
						if (check_access(data, (int []){j - 1, i}, (int []){j + 1, i}))
						{
							printf("Cave found\n");
							data->map_copy[i][j] = '1';
							mapcpy(data->map, data->map_copy);
							pg(data->map_copy, (int []){j,i+1}, NULL, data);
							mapcpy(data->map_cave, data->map_copy);
							mapcpy(data->map_copy, data->map);
							pg(data->map_copy, (int []){j,i-1}, NULL, data);
							data->map_copy[i][j] = 'H';
							data->map_cave[i][j] = 'H';
						}
						else 
							printf("Cave not found\n");
						// propagate(data->map, (int []){i,j - 1}, (int []){i, j + 1}, data, NULL);
					}
			}
		}
	}
	set_tile(&data->map_copy, data);
	set_tile(&data->map_cave, data);
}