/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:13:38 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/28 14:16:56 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup_stack(t_data *data)
{
	t_node	*temp;

	while (data->stack != NULL)
	{
		temp = data->stack;
		data->stack = data->stack->next;
		free(temp);
	}
	data->stack = NULL;
}

void	push(t_node	**top, int x, int y)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
	{
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
		return ;
	}
	temp = *top;
	*top = (*top)->next;
	free(temp);
}

void	*free_new_map(char **new_map, int i)
{
	while (--i >= 0)
		free(new_map[i]);
	free(new_map);
	return (NULL);
}
