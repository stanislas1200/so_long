/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:59:20 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/25 13:26:05 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_more(t_data *data)
{
	if (data->map)
	{
		free(data->map);
		if (data->map_copy)
			free(data->map_copy);
		if (data->map_cave)
			free(data->map_cave);
	}
	if (data->img)
		free(data->img);
	while (data->trap_list)
	{
		t_trap	*tmp;

		tmp = data->trap_list;
		data->trap_list = data->trap_list->next;
		free(tmp);
	}
	while (data->enemy_list)
	{
		t_enemy	*tmp;

		tmp = data->enemy_list;
		data->enemy_list = data->enemy_list->next;
		free(tmp);
	}
	if (data)
		free(data);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (data->player_possition)
		free(data->player_possition);
	if (data->exit_possition)
		free(data->exit_possition);
	while (data->map && data->map[i])
	{
		free(data->map[i]);
		if (data->map_copy && data->map_copy[i])
			free(data->map_copy[i]);
		if (data->map_cave && data->map_cave[i])
			free(data->map_cave[i]);
		i++;
	}
	free_more(data);
}

void	data_setup(t_data *data)
{
	data->map = NULL;
	data->map_copy = NULL;
	data->map_cave = NULL;
	data->player_possition = NULL;
	data->exit_possition = NULL;
	data->img = NULL;
	data->trap_list = NULL;
	data->enemy_list = NULL;
	data->printed = 0;
	data->cave = 0;
	data->player_nbr = 0;
	data->exit_nbr = 0;
	data->collectible_nbr = 0;
	data->player_frame = 1;
	data->player_move_count = 0;
	data->collected_count = 0;
	data->reachable_end = 0;
	data->map_height = 0;
	data->map_width = 0;
	data->direction = 0;
	data->time = 0;
	data->design_mode = 0;
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("\x1b[1;31mError\x1b[0m: malloc failed\n");
		exit(1);
	}
	data_setup(data);
	if (ac == 2)
	{
		set_map_from_file(av[1], data);
		if (check_map_tiles(data, -1, -1))
		{
			if (data->reachable_end)
			{
				start_game(data);
			}
			else
			{
				printf("\x1b[1;31mError\x1b[0m: No acces to exit\n");
			}
		}
	}
	else
		printf("\x1b[33mWarning\x1b[0m: No Map\n");
	// mlx_destroy_window(mlx, mlx_win);
	// free(mlx);
	free_all(data);
	return (0);
}

// 1 more function