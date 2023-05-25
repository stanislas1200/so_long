/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:26:26 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/25 13:26:27 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*free_new_map(char **new_map, int i)
{
	while (--i >= 0)
		free(new_map[i]);
	free(new_map);
	return (NULL);
}

char	**new_mapcpy(char **map, int height, int width)
{
	char	**new_map;
	int		i;
	int		j;

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
			return (free_new_map(new_map, i));
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
	int	i;
	int	len;
	int	error;

	i = -1;
	len = ft_strlen(line);
	error = 1;
	while (line && line[++i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'C' \
		&& line[i] != 'E' && line[i] != 'P')
			printf("\x1b[1;31mError\x1b[0m: Map line\x1b[1;35m %d:%d\x1b[0m \
contains invalid characters\n", line_nbr + 1, i + 1);
		if (line_nbr == 0 && line[i] != '1')
			printf("\x1b[1;31mError\x1b[0m: Map line\x1b[1;35m %d:%d\x1b[0m \
is not closed\n", line_nbr + 1, i + 1);
		if ((i == 0 || i == len - 1) && line[i] != '1')
			printf("\x1b[1;31mError\x1b[0m: Map line\x1b[1;35m %d:%d\x1b[0m \
is not closed\n", line_nbr + 1, i + 1);
		if (last_line && line[i] != '1')
			printf("\x1b[1;31mError\x1b[0m: Map line\x1b[1;35m %d:%d\x1b[0m \
is not closed\n", line_nbr + 1, i + 1);
		if ((line[i] != '1' && line[i] != '0' && line[i] != 'C' && line[i] \
		!= 'E' && line[i] != 'P') || (line_nbr == 0 && line[i] != '1') || \
		((i == 0 || i == len - 1) && line[i] != '1') || (last_line && line[i] \
		!= '1'))
			error = 0;
	}
	return (error);
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
int	check_common_errors(t_data *data)
{
	int	error;

	error = 1;
	if (data->player_nbr > 1)
		printf("\x1b[1;31mError\x1b[0m: Too many player on the map\n");
	if (data->exit_nbr > 1)
		printf("\x1b[1;31mError\x1b[0m: Too many exit on the map\n");
	if (data->player_nbr < 1)
		printf("\x1b[1;31mError\x1b[0m: No player on the map\n");
	if (data->exit_nbr < 1)
		printf("\x1b[1;31mError\x1b[0m: No exit on the map\n");
	if (data->collectible_nbr == 0)
		printf("\x1b[1;31mError\x1b[0m: No collectible on the map\n");
	if (data->player_nbr > 1 || data->exit_nbr > 1 || data->player_nbr < 1 \
	|| data->exit_nbr < 1 || data->collectible_nbr == 0)
		error = 0;
	return (error);
}

void	check_collectible_access(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'C')
			{
				printf("\x1b[1;31mError\x1b[0m: No acces to \x1b[33m\
Collectible\x1b[0m line \x1b[1;35m%d:%d\x1b[0m\n", \
				i + 1, j + 1);
				data->reachable_end = 0;
			}
		}
	}
}

int	check_map_tiles_helper(t_data *data, int i, int j)
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
		return (0);
	if (data->exit_nbr > 1)
		return (0);
	return (1);
}
