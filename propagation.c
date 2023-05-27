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
	int x;
	int y;
	struct s_node* next;
} t_node;

void cleanup_stack(t_node* stack) {
    while (stack != NULL) {
        t_node* temp = stack;
        stack = stack->next;
        free(temp);
    }
}

void push(t_node** top, int x, int y)
{
	t_node* newNode = (t_node*)malloc(sizeof(t_node));
	if (newNode == NULL)
	{
		// Handle memory allocation failure
		return;
	}

	newNode->x = x;
	newNode->y = y;
	newNode->next = *top;
	*top = newNode;
}

void pop(t_node** top)
{
	if (*top == NULL)
	{
		// Handle empty stack
		return;
	}

	t_node* temp = *top;
	*top = (*top)->next;
	free(temp);
}

int isStackEmpty(t_node* top)
{
	return (top == NULL);
}

void pg2(char** map, int* start, int* end, t_data* data)
{
	int i, j;
	t_node* stack = NULL;

	push(&stack, start[0], start[1]);

	while (!isStackEmpty(stack))
	{
		int x = stack->x;
		int y = stack->y;
		pop(&stack);

		if (x == end[0] && y == end[1])
		{
			data->cave = 1;
			cleanup_stack(stack); // Clean up the stack before returning
			return;
		}

		if (map[y][x] == '1')
		{
			int i, j;
			map[y][x] = '#';

			for (i = -2; i < 2; i++)
			{
				for (j = -2; j < 2; j++)
				{
					if ((i == 0 || j == 0) && x + j >= 0 && x + j < data->map_width && y + i >= 0 && y + i < data->map_height && map[y + i][x + j])
					{
						push(&stack, x + j, y + i);
					}
				}
			}
		}
	}
	cleanup_stack(stack); // Clean up the stack before returning
}

int check_access(t_data* data, int* start, int* end)
{
	int cave = 0;
	pg2(data->map, start, end, data);
	if (cave)
		return 1;
	return 0;
}

void pg(char** map, int* start, int* end, t_data* data)
{
	int i, j;
	t_node* stack = NULL;

	push(&stack, start[0], start[1]);

	while (!isStackEmpty(stack))
	{
		t_node* node = stack;
		int x = node->x;
		int y = node->y;
		pop(&stack);

		if (end && x == end[0] && y == end[1])
		{
			data->reachable_end = 1;
			// cleanup_stack(stack); // Clean up the stack before returning
			// return;
		}


		if (map[y][x] == '0' || map[y][x] == 'H' || map[y][x] == 'C' || map[y][x] == 'E' || map[y][x] == 'P')
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
			// for (i = -1; i <= 1; i++)
			// 		for (j = -1; j <= 1; j++)
			// 			if (i != 0 || j != 0)
			// 				if (y + i >= 0 && y + i < data->map_height && x + j >= 0 && x + j < data->map_width && map[y + i][x + j])
			// 					push(&stack, x + j, y + i);
		}
	}
	
	cleanup_stack(stack); // Clean up the stack before returning
}

