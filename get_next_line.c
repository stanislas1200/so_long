/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:58:18 by sgodin            #+#    #+#             */
/*   Updated: 2022/11/26 18:10:34 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free_strs(char **str, char **str2)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	if (str2 && *str2)
	{
		free(*str2);
		*str2 = NULL;
	}
}

char	*ft_get_line(const char *next)
{
	char	*line;
	int		i;

	i = 0;
	if (!next[i])
		return (NULL);
	while (next[i] && next[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	if (next[i] && next[i] == '\n')
		line[i] = '\n';
	while (--i >= 0 && next[i])
		line[i] = next[i];
	return (line);
}

char	*ft_next_line(char *buffer)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	ret = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!ret)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		ret[j++] = buffer[i++];
	free(buffer);
	return (ret);
}

void	ft_read_file(int fd, char **next)
{
	char	*buffer;
	int		byte_size;
	char	*temp;

	temp = NULL;
	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return ;
	byte_size = 1;
	while (byte_size > 0)
	{
		byte_size = read(fd, buffer, BUFFER_SIZE);
		if (byte_size == -1)
		{
			ft_free_strs(&buffer, next);
			return ;
		}
		buffer[byte_size] = '\0';
		temp = ft_strjoin(*next, buffer);
		free(*next);
		*next = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	ft_free_strs(&buffer, 0);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*next;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	line = NULL;
	if (!next)
		next = ft_strdup("");
	ft_read_file(fd, &next);
	if (next != NULL && *next != '\0')
	{
		line = ft_get_line(next);
		next = ft_next_line(next);
	}
	if (!line || *line == '\0')
	{
		ft_free_strs(&next, &line);
		return (NULL);
	}
	return (line);
}
