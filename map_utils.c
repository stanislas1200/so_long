#include "so_long.h"

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
 * Splits a string into an array of strings, with each string corresponding to a line
 * terminated by a newline character ('\n').
 *
 * @param all_line The string to split.
 * @param len The maximum length of each line (excluding the null terminator).
 *
 * @return An array of strings, with each string corresponding to a line in the original string.
 *         The last element of the array is NULL.
 *         Returns NULL on error.
 */
char **split_lines(char *all_line, int len)
{
	int i;
	int j;
	int tab_size;
	char **tab;

	i = 0;
	tab_size = 0;
	while (all_line[i])
	{
		if (all_line[i] == '\n')
			tab_size++;
		i++;
	}
	tab = malloc(sizeof(char *) * (tab_size + 2));
	if (!tab)
		return (NULL);
	i = 0;
	tab[tab_size + 1] = NULL;
	j = 0;
	tab[i] = malloc(sizeof(char) * len + 2);
	if (!tab[i])
	{
		while (i >= 0)
			free(tab[i--]);
		free(tab);
		return (NULL);
	}
	while (*all_line)
	{
		tab[i][j++] = *all_line++;
		if (*all_line == '\r')
			all_line++;
		if (*all_line == '\n')
		{
			tab[i][j] = '\0';
			i++;
			j = 0;
			tab[i] = malloc(sizeof(char) * len + 2);
			if (!tab[i])
			{
				while (i >= 0)
					free(tab[i--]);
				free(tab);
				return (NULL);
			}
			all_line++;
		}
	}
	tab[i][j] = '\0';
	return tab;
}

/**
 * Opens a file at the specified path and returns its file descriptor.
 *
 * @param path The path of the file to open.
 *
 * @return Returns the file descriptor of the opened file, or -1 on error.
 */
int open_file(char *path)
{
	int		i = -1;
	char	*new_path = NULL;
	int		fd;
	int		free_path = 0;
	while (path[++i])
		if (path[i] == '.' && !(path[i + 1] == '/' && !path[i - 1]))
			if (path[i + 1] == 'b' && path[i + 2] == 'e' && path[i + 3] == 'r' && path[i + 4] == '\0')
				break;
			else
			{
				printf("\x1b[1;31mError\x1b[0m: Map file must be a\x1b[1;35m .ber\x1b[0m file\n");
				return (-2);
			}
		else if (path[i + 1] == '\0')
				new_path = ft_strjoin(path, ".ber");
	if (new_path)
	{
		path = new_path;
		free_path = 1;
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		new_path = ft_strjoin("./data/map/", path);
		if (new_path)
		{
			fd = open(new_path, O_RDONLY);
			free(new_path);
		}
	}
	if (free_path)
		free(path);
	return fd;
}

/**
 * Reads the contents of a file given by its file descriptor.
 *
 * @param fd The file descriptor of the file to read.
 *
 * @return Returns a pointer to the contents of the file as a string, or NULL on error.
 */
char *read_file(int fd, t_data *data)
{
	char *line = NULL;
	char *all_line;
	char *tmp = NULL;
	line = get_next_line(fd);
	if (!line)
	{
		printf("\x1b[1;31mError\x1b[0m: Map is empty\n");
		return (NULL);
	}
	int i = ft_strlen(line);
	int j = 0;
	all_line = ft_strjoin("", line);
	if (!all_line)
	{
		while (line)
		{
			free(line);
			line = get_next_line(fd);
		}
		return (NULL);
	}
	int k = 0;
	while (line)
	{
		k = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
		if (!line)
			i -= 2; // -2 on windows
		else
		{
			tmp = ft_strjoin(all_line, line);
			if (!tmp)
			{
				while (line)
				{
					free(line);
					line = get_next_line(fd);
				}
				free(all_line);
				return (NULL);
			}
			free(all_line);
			all_line = tmp;
		}
		if (i != k)
		{
			printf("\x1b[1;31mError\x1b[0m: Map line\x1b[1;35m %d and %d\x1b[0m doesn't have the same lenght\n", j, j + 1);
			while (line)
			{
				free(line);
				line = get_next_line(fd);
			}
			free(all_line);
			return (NULL);
		}
		j++;
	}
	data->map_width = k;
	data->map_height = j;
	return all_line;
}

char **new_mapcpy(char **map, int height, int width)
{
	char **new_map;
	int i;
	int j;

	i = -1;
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

/**
 * Reads a file at the specified path and sets the map to the contents of the file.
 *
 * @param path The path of the file to read.
 * @param map A pointer to the map, which will be set to the contents of the file.
 * @param data A pointer to a t_data struct that contains data about the map.
 *
 */
void set_map_from_file(char *path, t_data *data)
{
	int	fd;
	char *all_line;
	/*Try open map*/
	fd = open_file(path);
	if (fd == -1)
		perror("\x1b[1;31mError\x1b[0m");
	if (fd == -2 || fd == -1)
	{
		free(data);
		exit(1);
	}
	/*Try read map*/
	all_line = read_file(fd, data);
	if (!all_line)
	{
		free(data);
		exit(1);
	}
	/*Try split map*/
	// printf("\nAll line : \n%s\n len : %d\n", all_line, data->map_width);
	int i = 0;
	while (all_line[i])
		i++;
	data->map = split_lines(all_line, data->map_width);
	if (!data->map)
	{
		free(all_line);
		free(data);
		exit(1);
	}
	data->map_copy = new_mapcpy(data->map, data->map_height, data->map_width);
	if (!data->map_copy)
	{
		free(all_line);
		i = -1;
		while (data->map[++i])
			free(data->map[i]);
		free(data->map);
		free(data);
		exit(1);
	}
	data->map_cave = new_mapcpy(data->map, data->map_height, data->map_width);
	if (!data->map_cave)
	{
		free(all_line);
		i = -1;
		while (data->map[++i])
			free(data->map[i]);
		free(data->map);
		i = -1;
		while (data->map_copy[++i])
			free(data->map_copy[i]);
		free(data->map_copy);
		free(data);
		exit(1);
	}
	free(all_line);
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

char get_wall_tile(t_data *data, int i, int j) {
    char tile = data->map_copy[i][j];
    
    if (tile == '1') {
        // Check neighboring tiles to determine wall tile
        if (i > 0 && ((data->map_copy[i-1][j] < '0' || data->map_copy[i-1][j] > '9'))) { // Check top tile
            if (j > 0 && (data->map_copy[i][j-1] < '0' || data->map_copy[i][j-1] > '9')) { // Check left tile
                tile = '2';
            } else if (j < data->map_width - 1 && (data->map_copy[i][j+1] < '0' || data->map_copy[i][j+1] > '9')) { // Check right tile
                tile = '4';
            } else {
                tile = '3';
            }
        }
        else if (i < data->map_height - 1 && (data->map_copy[i+1][j] < '0' || data->map_copy[i+1][j] > '9')) { // Check bottom tile
            if (j > 0 && (data->map_copy[i][j-1] < '0' || data->map_copy[i][j-1] > '9')) { // Check left tile
                tile = '7';
            } else if (j < data->map_width - 1 && (data->map_copy[i][j+1] < '0' || data->map_copy[i][j+1] > '9')) { // Check right tile
                tile = '9';
            } else {
                tile = '8';
            }
        }
        else if (j > 0 && (data->map_copy[i][j-1] < '0' || data->map_copy[i][j-1] > '9')) { // Check left tile
            tile = '0';
        }
        else if (j < data->map_width - 1 && (data->map_copy[i][j+1] < '0' || data->map_copy[i][j+1] > '9')) { // Check right tile
            tile = '6';
        }
        else tile = '5';
    }
    return tile;
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
							
						}
						else 
							printf("Cave not found\n");
						// propagate(data->map, (int []){i,j - 1}, (int []){i, j + 1}, data, NULL);
					}
			}
	}
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map_copy[i][j] == '1'){
                if ((i > 0 && i < 9) && (data->map_copy[i-1][j] >= 'A' && data->map_copy[i+1][j] >= 'A'))
                data->map_copy[i][j] = 'W';
            else if ((j > 0 && j < 19) && (data->map_copy[i][j-1] >= 'A' && data->map_copy[i][j+1] >= 'A'))
                data->map_copy[i][j] = 'W';
            }
		}
	}
	i = -1;
	while (data->map_copy[++i])
	{
		j = -1;
		while (data->map_copy[i][++j])
			data->map_copy[i][j] = get_wall_tile(data, i, j);
	}
	i = -1;
	while (data->map_copy[++i])
	{
		j = -1;
		while (data->map_copy[i][++j])
			if (data->map_copy[i][j] == '5')
				{
					if (i > 0 && (data->map_copy[i - 1][j] == '6' || data->map_copy[i - 1][j] == '4') && (j < data->map_width - 1 && (data->map_copy[i][j + 1] == '3' || data->map_copy[i][j + 1] == '4')))
						data->map_copy[i][j] = 'B';
					else if (i > 0 && (data->map_copy[i - 1][j] == '2' || data->map_copy[i - 1][j] == '0') && (j > 0 && (data->map_copy[i][j - 1] == '3' || data->map_copy[i][j - 1] == '2')))
						data->map_copy[i][j] = 'D';
					else if (i < data->map_height - 1 && (data->map_copy[i + 1][j] == '0' || data->map_copy[i + 1][j] == '7') && (j > 0 && (data->map_copy[i][j - 1] == '7' || data->map_copy[i][j - 1] == '8')))
						data->map_copy[i][j] = 'A';
					else if (i < data->map_height - 1 && (data->map_copy[i + 1][j] == '6' || data->map_copy[i + 1][j] == '9') && (j < data->map_width - 1 && (data->map_copy[i][j + 1] == '8' || data->map_copy[i][j + 1] == '9')))
						data->map_copy[i][j] = '1';
				}
	}
}