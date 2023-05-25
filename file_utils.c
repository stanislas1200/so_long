/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:27:06 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/25 13:27:07 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*free_gnl(char *line, int fd)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

char	*read_file_helper2(char *all_line, char *line, int fd)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(all_line, line);
	free(all_line);
	if (!tmp)
		return (free_gnl(line, fd));
	return (tmp);
}

char	*read_file_helper(t_data *data, char *all_line, char *line, int fd)
{
	int	i;

	i = ft_strlen(line);
	while (line && all_line)
	{
		data->map_width = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
		if (!line)
			i -= 1; // -2 on windows
		else
			all_line = read_file_helper2(all_line, line, fd);
		if (i != data->map_width)
		{
			printf("\x1b[1;31mError\x1b[0m: Map line\x1b[1;35m %d and \
%d\x1b[0m doesn't have the same lenght\n", data->map_height, \
			data->map_height + 1);
			free(all_line);
			return (free_gnl(line, fd));
		}
		data->map_height++;
	}
	return (all_line);
}

/**
 * Reads the contents of a file given by its file descriptor.
 *
 * @param fd The file descriptor of the file to read.
 *
 * @return Returns a pointer to the contents of the file as a string, or NULL on error.
 */
char	*read_file(int fd, t_data *data)
{
	char	*line;
	char	*all_line;

	line = NULL;
	all_line = NULL;
	line = get_next_line(fd);
	if (!line)
	{
		printf("\x1b[1;31mError\x1b[0m: Map is empty\n");
		return (NULL);
	}
	all_line = ft_strjoin("", line);
	if (!all_line)
		return (free_gnl(line, fd));
	all_line = read_file_helper(data, all_line, line, fd);
	return (all_line);
}

/**
 * Reads a file at the specified path and sets the map to the contents of the file.
 *
 * @param path The path of the file to read.
 * @param map A pointer to the map, which will be set to the contents of the file.
 * @param data A pointer to a t_data struct that contains data about the map.
 *
 */
void	set_map_from_file(char *path, t_data *data)
{
	int		fd;
	char	*all_line;

	fd = open_file(path);
	if (fd == -1)
		perror("\x1b[1;31mError\x1b[0m");
	if (fd == -2 || fd == -1)
	{
		free(data);
		exit(1);
	}
	all_line = read_file(fd, data);
	if (all_line)
		data->map = split_lines(all_line, data->map_width, NULL, 0);
	data->map_copy = new_mapcpy(data->map, data->map_height, data->map_width);
	data->map_cave = new_mapcpy(data->map, data->map_height, data->map_width);
	if (!data->map_cave || !data->map_copy || !data->map)
	{
		free_all(data);
		free(all_line);
		exit(1);
	}
	free(all_line);
}
