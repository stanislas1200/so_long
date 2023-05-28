/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:46:39 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/28 16:21:44 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len = 1;
	while (nbr != 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	int		i;

	i = get_len(nbr);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (nbr == 0)
		str[i] = '0';
	while (nbr != 0)
	{
		str[i--] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (str);
}

void	*get_tile_helper(t_data *data, char tile)
{
	if (tile == 'A')
		return (data->arr[11]);
	else if (tile == 'B')
		return (data->arr[12]);
	else if (tile == 'D')
		return (data->arr[13]);
	else if (tile == 'H' || tile == 'P')
		return (data->arr[14]);
	else if (tile == 'C')
	{
		if ((data->time / 10) % 2)
			return (data->arr[15]);
		return (data->arr[16]);
	}
	else if (tile == 'E')
	{
		if (data->collectible_nbr == 0)
			return (data->img->exit_on[(data->time / 10) % 4]);
		else
			return (data->img->exit_tile);
	}
	else if (tile == '-')
		return (data->arr[17]);
	else
		return (data->img->unknown_tile);
}

	/*
	EPCH

	234
	056
	789 W

	1A
	BD
	*/
void	*get_tile(t_data *data, char tile)
{
	if (tile == '2')
		return (data->arr[0]);
	else if (tile == '3')
		return (data->arr[1]);
	else if (tile == '4')
		return (data->arr[2]);
	else if (tile == '0')
		return (data->arr[3]);
	else if (tile == '5')
		return (data->arr[4]);
	else if (tile == '6')
		return (data->arr[5]);
	else if (tile == '7')
		return (data->arr[6]);
	else if (tile == '8')
		return (data->arr[7]);
	else if (tile == '9')
		return (data->arr[8]);
	else if (tile == 'W')
		return (data->arr[9]);
	else if (tile == '1')
		return (data->arr[10]);
	else
		return (get_tile_helper(data, tile));
}

void	move_enemy(t_data *data, t_enemy *enemy)
{
	int	*pos;

	pos = (int []){enemy->x, enemy->y};
	if (enemy->direction == 0)
		pos[1] -= 1;
	else if (enemy->direction == 1)
		pos[1] += 1;
	else if (enemy->direction == 2)
		pos[0] += 1;
	else if (enemy->direction == 3)
		pos[0] -= 1;
	if (data->map[pos[1]][pos[0]] == '1' || data->map[pos[1]][pos[0]] == '#')
	{
		enemy->direction = (enemy->direction + rand()) % 4;
		return ;
	}
	enemy->x = pos[0];
	enemy->y = pos[1];
}

void	update_portal(t_data *data)
{
	if (data->cave && data->map_cave[data->exit_possition[1]][data->exit_possition[0]] != '5' && !data->design_mode)
	{
		mlx_put_image_to_window(data->mlx, data->win, get_tile(data, data->ptr[data->exit_possition[1]][data->exit_possition[0]]), \
		data->exit_possition[0] * 50, data->exit_possition[1] * 50);
		if (data->collectible_nbr == 0)
			mlx_put_image_to_window(data->mlx, data->win, data->img->exit_on[(data->time / 10) % 4], \
			data->exit_possition[0] * 50, data->exit_possition[1] * 50);
		else
			mlx_put_image_to_window(data->mlx, data->win, data->img->exit_tile, \
			data->exit_possition[0] * 50, data->exit_possition[1] * 50);
	}
	else if (!data->cave && data->map_copy[data->exit_possition[1]][data->exit_possition[0]] != '5' && !data->design_mode)
	{
		mlx_put_image_to_window(data->mlx, data->win, get_tile(data, data->ptr[data->exit_possition[1]][data->exit_possition[0]]), \
		data->exit_possition[0] * 50, data->exit_possition[1] * 50);
		if (data->collectible_nbr == 0)
			mlx_put_image_to_window(data->mlx, data->win, data->img->exit_on[(data->time / 10) % 4], \
			data->exit_possition[0] * 50, data->exit_possition[1] * 50);
		else
			mlx_put_image_to_window(data->mlx, data->win, data->img->exit_tile, \
			data->exit_possition[0] * 50, data->exit_possition[1] * 50);
	}
}

void	update_trap(t_data *data)
{
	t_trap *current = data->trap_list;
	while (current != NULL)
	{
		current->frame = (current->frame + 1) % 1001;
		if (current->x == data->player_possition[0] && current->y == data->player_possition[1])
		{
			if ((current->frame / 10) % 9 == 7)
			{	
				printf("You lose!\n");
				mlx_clear_window(data->mlx, data->win);
				mlx_destroy_window(data->mlx, data->win);
				// if (data->mlx)
				// 	free(data->mlx);
				// free_all(data);
				// system("leaks so_long");
				exit(0);
			}
		}
		if (data->design_mode)
		{
			int y = data->player_possition[1] - 5;
			int x = data->player_possition[0] - 10;
			if (-1 + y < 0)
				y = 0;
			if (-1 + x < 0 )
				x = 0;
			if (10 + y > data->map_height)
				y = data->map_height - 10;
			if (20 + x > data->map_width)
				x = data->map_width - 20;
			int i = -1;
			while (++i < 10)
			{
				int j = -1;
				while (++j < 20)
				{
					if (current->x == j + x && current->y == i + y)
					{
						mlx_put_image_to_window(data->mlx, data->win, get_tile(data, data->ptr[current->y][current->x]), \
						j * 50, i * 50);
						mlx_put_image_to_window(data->mlx, data->win, data->img->trap[(current->frame / 10) % 9], \
						j * 50, i * 50);
					}
				}
			}
		}
		else if (data->cave && data->map_cave[current->y][current->x] != '5')
		{
			mlx_put_image_to_window(data->mlx, data->win, get_tile(data, data->ptr[current->y][current->x]), \
			current->x * 50, current->y * 50);
			mlx_put_image_to_window(data->mlx, data->win, data->img->trap[(current->frame / 10) % 9], \
			current->x * 50, current->y * 50);
		}
		else if (!data->cave && data->map_copy[current->y][current->x] != '5')
		{
			mlx_put_image_to_window(data->mlx, data->win, get_tile(data, data->ptr[current->y][current->x]), \
			current->x * 50, current->y * 50);
			mlx_put_image_to_window(data->mlx, data->win, data->img->trap[(current->frame / 10) % 9], \
			current->x * 50, current->y * 50);
		}
		current = current->next;
	}
}

void	update_enemy(t_data *data)
{
	t_enemy *current = data->enemy_list;
	while (current != NULL)
	{
		current->frame = (current->frame + 1) % 1001;
		if (current->x == data->player_possition[0] && current->y == data->player_possition[1])
		{
			printf("You lose!\n");
				// system("leaks so_long");
			exit(0);
		}
		if (data->design_mode)
		{
			int y = data->player_possition[1] - 5;
			int x = data->player_possition[0] - 10;
			if (-1 + y < 0)
				y = 0;
			if (-1 + x < 0 )
				x = 0;
			if (10 + y > data->map_height)
				y = data->map_height - 10;
			if (20 + x > data->map_width)
				x = data->map_width - 20;
			int i = -1;
			while (++i < 10)
			{
				int j = -1;
				while (++j < 20)
				{
					if (current->x == j + x && current->y == i + y)
					{//temp
						mlx_put_image_to_window(data->mlx, data->win, get_tile(data, data->ptr[current->y - 1][current->x]), j * 50, (i-1) * 50);
						mlx_put_image_to_window(data->mlx, data->win, get_tile(data, data->ptr[current->y + 1][current->x]), j * 50, (i+1) * 50);
						mlx_put_image_to_window(data->mlx, data->win, get_tile(data, data->ptr[current->y][current->x]), j * 50, i * 50);
						mlx_put_image_to_window(data->mlx, data->win, get_tile(data, data->ptr[current->y][current->x + 1]), (j+1) * 50, i * 50);
						mlx_put_image_to_window(data->mlx, data->win, get_tile(data, data->ptr[current->y][current->x - 1]), (j-1) * 50, i * 50);
						if ((current->frame) % 80 == 0)
							move_enemy(data, current);
						mlx_put_image_to_window(data->mlx, data->win, data->img->enemy[current->direction][(current->frame / 10) % 4], \
						j * 50, i * 50);
					}
				}
			}
		}
		else if (data->cave && data->map_cave[current->y][current->x] != '5')
		{
			mlx_put_image_to_window(data->mlx, data->win, get_tile(data, data->ptr[current->y][current->x]), \
			current->x * 50, current->y * 50);
			if ((current->frame) % 10 == 0)
				move_enemy(data, current);
			mlx_put_image_to_window(data->mlx, data->win, data->img->enemy[current->direction][(current->frame / 10) % 4], \
			current->x * 50, current->y * 50);
		}
		else if (!data->cave && data->map_copy[current->y][current->x] != '5')
		{
			mlx_put_image_to_window(data->mlx, data->win, get_tile(data, data->ptr[current->y][current->x]), \
			current->x * 50, current->y * 50);
			if ((current->frame) % 50 == 0)
				move_enemy(data, current);
			mlx_put_image_to_window(data->mlx, data->win, data->img->enemy[current->direction][(current->frame / 10) % 4], \
			current->x * 50, current->y * 50);
		}
		current = current->next;
	}
}

void	update_player_frame(t_data *data)
{
	if (data->design_mode)
	{
		if (data->player_possition[0] >= 10 && data->player_possition[1] >= 5 && data->player_possition[0] < data->map_width - 10 && data->player_possition[1] < data->map_height - 5)
			mlx_put_image_to_window(data->mlx, data->win, data->img->\
			player[data->direction][(data->time / 10) % 4], \
			10 * 50, 5 * 50);
	}
	else
		mlx_put_image_to_window(data->mlx, data->win, data->img->\
		player[data->direction][(data->time / 10) % 4], \
		data->player_possition[0] * 50, data->player_possition[1] * 50);
}

int	update_frame(t_data *data)
{
	if (data->time >= 1000)
		data->time = 0;
	if (data->design_mode)
	{
		if (data->player_possition[0] >= 10 && data->player_possition[1] >= 5 && data->player_possition[0] < data->map_width - 10 && data->player_possition[1] < data->map_height - 5)
			mlx_put_image_to_window(data->mlx, data->win, get_tile(data, data->ptr[data->exit_possition[1]][data->exit_possition[0]]), 10 * 50, 5 * 50);
	}
	else
	{
		mlx_put_image_to_window(data->mlx, data->win, get_tile(data, data->ptr[data->player_possition[1]][data->player_possition[0]]), \
		data->player_possition[0] * 50, data->player_possition[1] * 50);
	}
	update_portal(data);
	update_trap(data);
	update_enemy(data);
	update_player_frame(data);
	data->time++;
	return (0);
}

void	setting_mlx(t_data *data)
{
	if (data->map_height > 28 || data->map_width > 50)
		data->design_mode = 1;
	data->mlx = mlx_init();
	if (data->design_mode)
		data->win = mlx_new_window(data->mlx, 1000, 500, \
		"The Mysterious Firefly Cave");
	else
		data->win = mlx_new_window(data->mlx, 50 * data->map_width, 50 * \
		data->map_height, "The Mysterious Firefly Cave");
}

void	load_image4(t_data *data)
{
	data->img->player_right_0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyRight.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_right_1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyRight1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_right_2 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyRight2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_right_3 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyRight3.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[0][0] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_up0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[0][1] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_up1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[0][2] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_up2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[0][3] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_up1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[1][0] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_down0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[1][1] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_down1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[1][2] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_down2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[1][3] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_down1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[3][0] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_left0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[3][1] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_left1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[3][2] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_left2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[3][3] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_left1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[2][0] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_right0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[2][1] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_right1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[2][2] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_right2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->enemy[2][3] = mlx_xpm_file_to_image(data->mlx, "./data/texture/enemy/enemy_right1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->trap[0] = mlx_xpm_file_to_image(data->mlx, "./data/texture/trap0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->trap[1] = mlx_xpm_file_to_image(data->mlx, "./data/texture/trap0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->trap[2] = mlx_xpm_file_to_image(data->mlx, "./data/texture/trap0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->trap[3] = mlx_xpm_file_to_image(data->mlx, "./data/texture/trap0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->trap[4] = mlx_xpm_file_to_image(data->mlx, "./data/texture/trap1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->trap[5] = mlx_xpm_file_to_image(data->mlx, "./data/texture/trap2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->trap[6] = mlx_xpm_file_to_image(data->mlx, "./data/texture/trap3.xpm", &data->img->img_width, &data->img->img_height);
	data->img->trap[7] = mlx_xpm_file_to_image(data->mlx, "./data/texture/trap4.xpm", &data->img->img_width, &data->img->img_height);
	data->img->trap[8] = mlx_xpm_file_to_image(data->mlx, "./data/texture/trap5.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_on[0] = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/portal_on0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_on[1] = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/portal_on1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_on[2] = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/portal_on2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_on[3] = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/portal_on3.xpm", &data->img->img_width, &data->img->img_height);
}

void	load_image3(t_data *data)
{
	data->img->cave_wall_itop_corner_right = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_itop_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_idown_corner_left = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_idown_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_idown_corner_right = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_idown_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_down = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_down.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_top = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_top.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_left = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_right = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_solo = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_solo.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_door = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_door.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_down_0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyDown.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_down_1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyDown1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_down_2 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyDown2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_down_3 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyDown3.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_up_0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyUp.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_up_1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyUp1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_up_2 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyUp2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_up_3 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyUp3.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_left_0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyLeft.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_left_1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyLeft1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_left_2 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyLeft2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_left_3 = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyLeft3.xpm", &data->img->img_width, &data->img->img_height);
	load_image4(data);
}

void	load_image2(t_data *data)
{
	data->img->wall_solo = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_solo.xpm", &data->img->img_width, &data->img->img_height);
	data->img->door = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/door.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/portal.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/portal_on0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/portal_on1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile2 = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/portal_on2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile3 = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/portal_on3.xpm", &data->img->img_width, &data->img->img_height);
	data->img->unknown_tile = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/unknown_tile.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_collectible0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_collectible0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_collectible1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_collectible1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_floor = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_floor.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_floor = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_floor.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_otop_corner_left = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_otop_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_otop_corner_right = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_otop_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_odown_corner_left = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_odown_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_odown_corner_right = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_odown_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_itop_corner_left = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_itop_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	load_image3(data);
}

void	load_image(t_data *data)
{
	data->img->collectible0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/collectible0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->collectible1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/collectible1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->floor = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/floor.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_floor = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_floor.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_otop_corner_left = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_otop_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_otop_corner_right = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_otop_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_odown_corner_left = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_odown_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_odown_corner_right = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_odown_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_itop_corner_left = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_itop_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_itop_corner_right = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_itop_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_idown_corner_left = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_idown_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_idown_corner_right = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_idown_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_down = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_down.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_top = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_top.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_left = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_right = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_right.xpm", &data->img->img_width, &data->img->img_height);
	load_image2(data);
}

void	draw_map_helper(t_data *data)
{
	int		i;
	int		j;
	void	*img;

	i = -1;
	while (data->ptr[++i])
	{
		j = -1;
		while (data->ptr[i][++j])
		{
			if (data->ptr[i][j] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->arr[14], \
						j * 50, i * 50);
			img = get_tile(data, data->ptr[i][j]);
			if (!img)
				mlx_put_image_to_window(data->mlx, data->win, \
				data->img->unknown_tile, j * 50, i * 50);
			else
				mlx_put_image_to_window(data->mlx, data->win, img, \
				j * 50, i * 50);
		}
	}
}

void	draw_player_chunck(t_data *data, int x, int y)
{
	if (x > 0 && x < data->map_width - 21)
		x = 10;
	else if (x > data->map_width - 22)
		x = data->player_possition[0] - data->map_width + 20;
	else
		x = data->player_possition[0];
	if (y > 0 && y < data->map_height - 11)
		y = 5;
	else if (y > data->map_height - 12)
		y = data->player_possition[1] - data->map_height + 10;
	else
		y = data->player_possition[1];
	mlx_put_image_to_window(data->mlx, data->win, data->img->\
	player[data->direction][(data->time / 10) % 4], \
	x * 50, y * 50);
}

void	draw_chunck_helper(t_data *data, int x, int y)
{
	int		i;
	int		j;
	void	*img;

	img = NULL;
	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 20)
		{
			img = get_tile(data, data->ptr[i + y][j + x]);
			if (!img)
				mlx_put_image_to_window(data->mlx, data->win, \
				data->img->unknown_tile, j * 50, i * 50);
			else
				mlx_put_image_to_window(data->mlx, data->win, img, \
				j * 50, i * 50);
		}
	}
}

void	draw_chunck(t_data *data)
{
	int		x;
	int		y;

	y = data->player_possition[1] - 5;
	x = data->player_possition[0] - 10;
	if (-1 + y < 0)
		y = 0;
	if (-1 + x < 0)
		x = 0;
	if (10 + y > data->map_height)
		y = data->map_height - 10;
	if (20 + x > data->map_width)
		x = data->map_width - 20;
	draw_chunck_helper(data, x, y);
	draw_player_chunck(data, x, y);
}

void	print_on_screen(t_data *data)
{
	int		i;
	char	*move;
	char	*nbr;

	move = ft_itoa(data->player_move_count);
	nbr = ft_itoa(data->collectible_nbr);
	if (!data->design_mode)
	{
		i = -1;
		while (++i < 4)
			mlx_put_image_to_window(data->mlx, data->win, \
				get_tile(data, data->ptr[0][i]), i * 50, 0);
	}
	mlx_string_put(data->mlx, data->win, 5, 10, 136, "Move Count: ");
	mlx_string_put(data->mlx, data->win, 160, \
	10, 136, move);
	mlx_string_put(data->mlx, data->win, 5, 25, 136, "Collected left: ");
	mlx_string_put(data->mlx, data->win, 160, \
	25, 136, nbr);
	free(move);
	free(nbr);
}

void	draw_map(t_data *data)
{
	if (data->design_mode)
		draw_chunck(data);
	else
		draw_map_helper(data);
	print_on_screen(data);
}

void	move_player2(int keycode, t_data *data, char **map)
{
	int	x;
	int	y;

	x = data->player_possition[0];
	y = data->player_possition[1];
	if (keycode == 12 || keycode == 123)
	{
		data->direction = 2;
		if (map[y][x - 1] != '1' && map[y][x - 1] != '#')
			data->player_possition[0]--;
	}
	else if (keycode == 2 || keycode == 124)
	{
		data->direction = 3;
		if (map[y][x + 1] != '1' && map[y][x + 1] != '#')
			data->player_possition[0]++;
	}
}

void	move_player(int keycode, t_data *data, char **map)
{
	int	x;
	int	y;

	x = data->player_possition[0];
	y = data->player_possition[1];
	if (keycode == 13 || keycode == 126)
	{
		data->direction = 0;
		if (map[y - 1][x] != '1' && map[y - 1][x] != '#')
			data->player_possition[1]--;
	}
	else if (keycode == 1 || keycode == 125)
	{
		data->direction = 1;
		if (map[y + 1][x] != '1' && map[y + 1][x] != '#')
			data->player_possition[1]++;
	}
	else
		move_player2(keycode, data, map);
	if (keycode == 2 || keycode == 12 || keycode == 1 || keycode == 13 \
	|| keycode == 124 || keycode == 123 || keycode == 125 || keycode == 126)
		data->player_move_count++;
}

void	exit_tile_check(t_data *data)
{
	if (data->ptr[data->player_possition[1]][data->player_possition[0]] \
	== 'E' && data->collectible_nbr == 0)
		printf("You win!\n");
}

void	do_tile_action(t_data *data)
{
	if (data->ptr[data->player_possition[1]][data->player_possition[0]] == 'C')
	{
		data->ptr[data->player_possition[1]][data->player_possition[0]] = 'H';
		data->collectible_nbr--;
	}
	else if (data->ptr[data->player_possition[1]][data->player_possition[0]] \
	== '-')
	{
		if (data->cave)
		{
			data->ptr = data->map_copy;
			data->arr = data->img->outside_tiles;
			data->cave = 0;
			data->player_possition[1] = data->player_possition[1] - 1;
		}
		else
		{
			data->ptr = data->map_cave;
			data->arr = data->img->inside_tiles;
			data->cave = 1;
			data->player_possition[1] = data->player_possition[1] + 1;
		}
		draw_map(data);
	}
	exit_tile_check(data);
}

void	end(void)
{
	printf("You lose!\n");
	system("leaks so_long");
	exit(0);
}

void	check_trap_collision(t_data *data)
{
	t_trap	*current;

	current = data->trap_list;
	while (current != NULL)
	{
		if (current->x == data->player_possition[0]
			&& current->y == data->player_possition[1])
		{
			if ((current->frame / 10) % 9 == 7)
				end();
			else
				break ;
		}
		current = current->next;
	}
}

int	key_press(int keycode, t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, \
	get_tile(data,
			data->ptr[data->player_possition[1]][data->player_possition[0]]),
		data->player_possition[0] * 50, data->player_possition[1] * 50);
	move_player(keycode, data, data->map);
	do_tile_action(data);
	if (data->design_mode)
		draw_map(data);
	else
		mlx_put_image_to_window(data->mlx, data->win, data->img->\
		player[data->direction][(data->time / 10) % 4], \
		data->player_possition[0] * 50, data->player_possition[1] * 50);
	check_trap_collision(data);
	print_on_screen(data);
	return (0);
}

void	image_setup3(t_data *data)
{
	data->img->player[3][0] = data->img->player_right_0;
	data->img->player[3][1] = data->img->player_right_1;
	data->img->player[3][2] = data->img->player_right_2;
	data->img->player[3][3] = data->img->player_right_3;
}

void	image_setup2(t_data *data)
{
	data->img->inside_tiles[6] = data->img->cave_wall_odown_corner_left;
	data->img->inside_tiles[7] = data->img->cave_wall_down;
	data->img->inside_tiles[8] = data->img->cave_wall_odown_corner_right;
	data->img->inside_tiles[9] = data->img->cave_wall_solo;
	data->img->inside_tiles[10] = data->img->cave_wall_itop_corner_left;
	data->img->inside_tiles[11] = data->img->cave_wall_itop_corner_right;
	data->img->inside_tiles[12] = data->img->cave_wall_idown_corner_left;
	data->img->inside_tiles[13] = data->img->cave_wall_idown_corner_right;
	data->img->inside_tiles[14] = data->img->cave_floor;
	data->img->inside_tiles[15] = data->img->cave_collectible0;
	data->img->inside_tiles[16] = data->img->cave_collectible1;
	data->img->inside_tiles[17] = data->img->cave_door;
	data->img->player[0][0] = data->img->player_up_0;
	data->img->player[0][1] = data->img->player_up_1;
	data->img->player[0][2] = data->img->player_up_2;
	data->img->player[0][3] = data->img->player_up_3;
	data->img->player[1][0] = data->img->player_down_0;
	data->img->player[1][1] = data->img->player_down_1;
	data->img->player[1][2] = data->img->player_down_2;
	data->img->player[1][3] = data->img->player_down_3;
	data->img->player[2][0] = data->img->player_left_0;
	data->img->player[2][1] = data->img->player_left_1;
	data->img->player[2][2] = data->img->player_left_2;
	data->img->player[2][3] = data->img->player_left_3;
	image_setup3(data);
}

void	image_setup(t_data *data)
{
	data->img->outside_tiles[0] = data->img->wall_otop_corner_left;
	data->img->outside_tiles[1] = data->img->wall_top;
	data->img->outside_tiles[2] = data->img->wall_otop_corner_right;
	data->img->outside_tiles[3] = data->img->wall_left;
	data->img->outside_tiles[4] = data->img->wall_floor;
	data->img->outside_tiles[5] = data->img->wall_right;
	data->img->outside_tiles[6] = data->img->wall_odown_corner_left;
	data->img->outside_tiles[7] = data->img->wall_down;
	data->img->outside_tiles[8] = data->img->wall_odown_corner_right;
	data->img->outside_tiles[9] = data->img->wall_solo;
	data->img->outside_tiles[10] = data->img->wall_itop_corner_left;
	data->img->outside_tiles[11] = data->img->wall_itop_corner_right;
	data->img->outside_tiles[12] = data->img->wall_idown_corner_left;
	data->img->outside_tiles[13] = data->img->wall_idown_corner_right;
	data->img->outside_tiles[14] = data->img->floor;
	data->img->outside_tiles[15] = data->img->collectible0;
	data->img->outside_tiles[16] = data->img->collectible1;
	data->img->outside_tiles[17] = data->img->door;
	data->img->inside_tiles[0] = data->img->cave_wall_otop_corner_left;
	data->img->inside_tiles[1] = data->img->cave_wall_top;
	data->img->inside_tiles[2] = data->img->cave_wall_otop_corner_right;
	data->img->inside_tiles[3] = data->img->cave_wall_left;
	data->img->inside_tiles[4] = data->img->cave_wall_floor;
	data->img->inside_tiles[5] = data->img->cave_wall_right;
	image_setup2(data);
}

void	start_game(t_data *data)
{
	map_setup(data);
	if (data->map_copy[data->player_possition[1]][data->player_possition[0]] \
	== 'P')
		data->cave = 0;
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		return ;
	setting_mlx(data);
	load_image(data);
	image_setup(data);
	if (data->cave)
	{
		data->ptr = data->map_cave;
		data->arr = data->img->inside_tiles;
	}
	else
	{
		data->ptr = data->map_copy;
		data->arr = data->img->outside_tiles;
	}
	draw_map(data);
	mlx_hook(data->win, 2, 0, &key_press, data);
	mlx_loop_hook(data->mlx, update_frame, data);
	mlx_loop(data->mlx);
}
// need no flame on exit 