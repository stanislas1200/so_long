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

typedef struct s_node
{
	int				x;
	int				y;
	struct s_node	*next;
}	t_node;

void	cleanup_stack(t_node	*stack)
{
	t_node	*temp;

	while (stack != NULL)
	{
		temp = stack;
		stack = stack->next;
		free(temp);
	}
}

void	push(t_node	**top, int x, int y)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
	{
		// Handle memory allocation failure
		return ;
	}
	node->x = x;
	node->y = y;
	node->next = *top;
	*top = node;
}

void	pop(t_node	**top)
{
	t_node	*temp;

	if (*top == NULL)
	{
		// Handle empty stack
		return ;
	}
	temp = *top;
	*top = (*top)->next;
	free(temp);
}

int	isstackempty(t_node	*top)
{
	return (top == NULL);
}

void	pg2(char	**map, int	*start, int	*end, t_data	*data)
{
	t_node	*stack;
	int		x;
	int		y;
	int		i;
	int		j;

	stack = NULL;
	push(&stack, start[0], start[1]);
	while (!isstackempty(stack))
	{
		y = stack->y;
		x = stack->x;
		pop(&stack);
		if (x == end[0] && y == end[1])
		{
			data->cave = 1;
			cleanup_stack(stack);
			return ;
		}
		if (map[y][x] == '1')
		{
			map[y][x] = '#';
			i = -2;
			while (++i < 2)
			{
				j = -2;
				while (++j < 2)
					if ((i == 0 || j == 0) && x + j >= 0 && \
					x + j < data->map_width && y + i >= 0 && \
					y + i < data->map_height && map[y + i][x + j])
						push(&stack, x + j, y + i);
			}
		}
	}
	cleanup_stack(stack);
}

int	check_access(t_data *data, int *start, int *end)
{
	int	cave;

	cave = 0;
	pg2(data->map, start, end, data);
	if (cave)
		return (1);
	return (0);
}

void	pg(char **map, int *start, int *end, t_data *data)
{
	int		i;
	int		j;
	t_node	*stack;
	t_node	*node;
	int		x;
	int		y;

	stack = NULL;
	push(&stack, start[0], start[1]);
	while (!isstackempty(stack))
	{
		node = stack;
		x = node->x;
		y = node->y;
		pop(&stack);
		if (end && x == end[0] && y == end[1])
			data->reachable_end = 1;
		if (map[y][x] == '0' || map[y][x] == 'H' || map[y][x] == 'C'
		|| map[y][x] == 'E' || map[y][x] == 'P')
		{
			if (end)
				map[y][x] = 'X';
			else
				map[y][x] = '5';
			i = -2;
			while (++i < 2)
			{
				j = -2;
				while (++j < 2)
					if ((i == 0 || j == 0) && map[i + start[1]][j + start[0]])
						push(&stack, x + j, y + i);
			}
		}
	}
	cleanup_stack(stack);
}
