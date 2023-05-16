#include "so_long.h"

void	*free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

int	split_helper(char ***tab, char **all_line, int *i)
{
	int	tab_size;

	*i = 0;
	tab_size = 0;
	while ((*all_line)[*i])
	{
		if ((*all_line)[*i] == '\n')
			tab_size++;
		(*i)++;
	}
	*tab = malloc(sizeof(char *) * (tab_size + 2));
	if (!(*tab))
		return (0);
	(*tab)[tab_size + 1] = NULL;
	*i = 0;
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
char	**split_lines(char *all_line, int len, char **tab, int j)
{
	int	i;

	if (!split_helper(&tab, &all_line, &i))
		return (NULL);
	tab[i] = malloc(sizeof(char) * len + 2);
	if (!tab[i])
		return (free_tab(tab));
	while (*all_line)
	{
		tab[i][j++] = *all_line++;
		if (*all_line == '\r')
			all_line++;
		if (*all_line == '\n')
		{
			tab[i++][j] = '\0';
			j = 0;
			tab[i] = malloc(sizeof(char) * len + 2);
			if (!tab[i])
				return (free_tab(tab));
			all_line++;
		}
	}
	tab[i][j] = '\0';
	return (tab);
}

int	find_file(char **path, char **new_path, int *free_path)
{
	int	i;

	i = -1;
	while ((*path)[++i])
	{
		if ((*path)[i] == '.' && !((*path)[i + 1] == '/' && !(*path)[i - 1]))
		{
			if ((*path)[i + 1] == 'b' && (*path)[i + 2] == 'e' && \
			(*path)[i + 3] == 'r' && (*path)[i + 4] == '\0')
				break ;
			else
			{
				printf("\x1b[1;31mError\x1b[0m: Map file must be \
a\x1b[1;35m .ber\x1b[0m file\n");
				return (-2);
			}
		}
		else if ((*path)[i + 1] == '\0')
			*new_path = ft_strjoin((*path), ".ber");
	}
	if (*new_path)
	{
		(*path) = *new_path;
		*free_path = 1;
	}
	return (0);
}

/**
 * Opens a file at the specified path and returns its file descriptor.
 *
 * @param path The path of the file to open.
 *
 * @return Returns the file descriptor of the opened file, or -1 on error.
 */
int	open_file(char *path)
{
	char	*new_path;
	int		fd;
	int		free_path;

	new_path = NULL;
	free_path = 0;
	if (find_file(&path, &new_path, &free_path) == -2)
		return (-2);
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
	return (fd);
}
