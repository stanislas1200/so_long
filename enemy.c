/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:19:24 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/28 14:32:00 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_enemy(t_enemy *new_enemy, t_enemy *current, t_data *data)
{
	new_enemy->x = data->j;
	new_enemy->y = data->i;
	new_enemy->frame = rand() % 1001;
	new_enemy->direction = rand() % 4;
	new_enemy->next = NULL;
	if (data->enemy_list == NULL)
	{
		data->enemy_list = new_enemy;
	}
	else
	{
		current = data->enemy_list;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_enemy;
	}
}

void	generate_enemy(t_data *data, int i, int j)
{
	t_enemy	*current;
	t_enemy	*new_enemy;

	new_enemy = NULL;
	current = NULL;
	if (rand() % 100 < 1)
	{
		data->i = i;
		data->j = j;
		new_enemy = (t_enemy *)malloc(sizeof(t_enemy));
		if (!new_enemy)
		{
			free_all(data);
			exit(1);
		}
		add_enemy(new_enemy, current, data);
	}
}

void	add_trap(t_trap *current, t_trap *new_trap, t_data *data)
{
	new_trap = (t_trap *)malloc(sizeof(t_trap));
	if (!new_trap)
	{
		free_all(data);
		exit(1);
	}
	new_trap->x = data->j;
	new_trap->y = data->i;
	new_trap->frame = rand() % 1001;
	new_trap->next = NULL;
	if (data->trap_list == NULL)
	{
		data->trap_list = new_trap;
	}
	else
	{
		current = data->trap_list;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_trap;
	}
}

void	generate_trap(t_data *data, int i, int j)
{
	t_trap	*current;
	t_trap	*new_trap;

	new_trap = NULL;
	current = NULL;
	data->i = i;
	data->j = j;
	if (data->map[i][j] != '1' && data->map[i][j] != '#' &&
		data->map[i][j] != 'C' && data->map[i][j] != 'E' &&
		data->map_copy[i][j] != 'C' && data->map_cave[i][j] != 'C' &&
		data->player_possition[0] != j)
	{
		if (data->map_copy[i - 1][j] == '-' || data->map_copy[i + 1][j] == '-')
			return ;
		if (rand() % 100 < 5)
			add_trap(current, new_trap, data);
		else
			generate_enemy(data, i, j);
	}
}

void	check_trap(t_data *data, int i, int j)
{
	t_trap	*tmp;
	t_trap	*current;

	current = data->trap_list;
	if (current != NULL)
	{
		tmp = current->next;
		if (current->x == j && current->y == i)
		{
			free(data->trap_list);
			current = tmp;
		}
		tmp = current;
		current = current->next;
	}
	while (current != NULL)
	{
		if (current->x == j && current->y == i)
		{
			tmp->next = current->next;
			free(current);
		}
		tmp = current;
		current = current->next;
	}
}
