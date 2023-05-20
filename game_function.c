/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:46:39 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/20 15:08:32 by sgodin           ###   ########.fr       */
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
	if (nbr < 0)
	{
		str[0] = '-';
		if (nbr == -2147483648)
		{
			str[1] = '2';
			nbr = 147483648;
		}
		else
			nbr *= -1;
	}
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

// int time = 0;
// int	update_frame(t_data *data) {
// 	if (time >= 1000)
// 	{
// 		mlx_put_image_to_window(data->mlx, data->win, data->floor, data->player_possition[0] * 50, data->player_possition[1] * 50);
// 		if (data->player_frame == 1)
// 		mlx_put_image_to_window(data->mlx, data->win, data->playerRight, data->player_possition[0] * 50, data->player_possition[1] * 50);
// 		else
// 		mlx_put_image_to_window(data->mlx, data->win, data->playerLeft, data->player_possition[0] * 50, data->player_possition[1] * 50);
// 		time = 0;
// 		data->player_frame *= -1;
// 	}
// 	time++;
// 	return (0);
// }



void	setting_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 50 * data->map_width, 50 * data->map_height, "The Mysterious Firefly Cave");
}

void	load_image(t_data *data)
{
	data->img = malloc(sizeof(t_img));
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
	data->img->wall_solo = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_solo.xpm", &data->img->img_width, &data->img->img_height);
	
	data->img->exit_tile = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/exit.xpm", &data->img->img_width, &data->img->img_height);
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
	data->img->cave_wall_itop_corner_right = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_itop_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_idown_corner_left = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_idown_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_idown_corner_right = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_idown_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_down = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_down.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_top = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_top.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_left = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_right = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_solo = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_solo.xpm", &data->img->img_width, &data->img->img_height);
	

	// data->playerUp = mlx_xpm_file_to_image(data->mlx, "./data/texture/fireflyUp.xpm", &data->img->img_width, &data->img->img_height);
	// data->playerDown = mlx_xpm_file_to_image(data->mlx, "./data/texture/fireflyDown.xpm", &data->img->img_width, &data->img->img_height);
	// data->playerLeft = mlx_xpm_file_to_image(data->mlx, "./data/texture/fireflyLeft.xpm", &data->img->img_width, &data->img->img_height);
	// data->playerRight = mlx_xpm_file_to_image(data->mlx, "./data/texture/fireflyRight.xpm", &data->img->img_width, &data->img->img_height);
}

// void	setting_map(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (data->map_copy[++i])
// 	{
// 		j = -1;
// 		while (data->map_copy[i][++j])
// 		{
// 			if (data->map_copy[i][j] == '1')
// 			{
// 				if (i > 0 && data->map_copy[i - 1][j] && data->map_copy[i - 1][j] != '1')
// 				{
// 					if (j < data->map_width - 1 && data->map_copy[i][j + 1] && data->map_copy[i][j + 1] != '1')
// 						mlx_put_image_to_window(data->mlx, data->win, data->wall1, j * 50, i * 50);
// 					else if (j > 0 && data->map_copy[i][j - 1] && data->map_copy[i][j - 1] != '1')
// 						mlx_put_image_to_window(data->mlx, data->win, data->wall0, j * 50, i * 50);
// 					else
// 						mlx_put_image_to_window(data->mlx, data->win, data->wall_top, j * 50, i * 50);
// 				}
// 				else if (i < data->map_height - 1 && data->map_copy[i + 1][j] && data->map_copy[i + 1][j] != '1')
// 				{
// 					if (j < data->map_width - 1 && data->map_copy[i][j + 1] && data->map_copy[i][j + 1] != '1')
// 						mlx_put_image_to_window(data->mlx, data->win, data->wall3, j * 50, i * 50);
// 					else if (j > 0 && data->map_copy[i][j - 1] && data->map_copy[i][j - 1] != '1')
// 						mlx_put_image_to_window(data->mlx, data->win, data->wall2, j * 50, i * 50);
// 					else
// 						mlx_put_image_to_window(data->mlx, data->win, data->wall_down, j * 50, i * 50);
// 				}
// 				else if (j > 0 && data->map_copy[i][j - 1] && data->map_copy[i][j - 1] != '1')
// 					mlx_put_image_to_window(data->mlx, data->win, data->wall_left, j * 50, i * 50);
// 				else if (j < data->map_width - 1 && data->map_copy[i][j + 1] && data->map_copy[i][j + 1] != '1')
// 					mlx_put_image_to_window(data->mlx, data->win, data->wall_right, j * 50, i * 50);
// 				else
// 					mlx_put_image_to_window(data->mlx, data->win, data->topfloor, j * 50, i * 50);
// 			}
// 			else if (data->map_copy[i][j] == 'C')
// 				mlx_put_image_to_window(data->mlx, data->win, data->coll, j * 50, i * 50);
// 			else if (data->map_copy[i][j] == 'P')
// 				mlx_put_image_to_window(data->mlx, data->win, data->playerUp, j * 50, i * 50);
// 			else if (data->map_copy[i][j] == '0')
// 				mlx_put_image_to_window(data->mlx, data->win, data->floor, j * 50, i * 50);
// 			else if (data->map_copy[i][j] == 'E')
// 				mlx_put_image_to_window(data->mlx, data->win, data->exit_tile, j * 50, i * 50);
// 		}
// 	}
// }

void	*draw_tile(t_data *data, char tile, void **arr)
{
	/*
	EPCH

	234
	056
	789 W

	1A
	BD
	*/
	if (tile == '2')
		return (arr[0]);// wall0 corner top left
	else if (tile == '3')
		return (arr[1]);// wall1 top
	else if (tile == '4')
		return (arr[2]);// wall2 corner top right
	else if (tile == '0')
		return (arr[3]);// wall3 left
	else if (tile == '5')
		return (arr[4]);// wall4 top floor
	else if (tile == '6')
		return (arr[5]);// wall5 right
	else if (tile == '7')
		return (arr[6]);// wall6 corner down left
	else if (tile == '8')
		return (arr[7]);// wall7 down
	else if (tile == '9')
		return (arr[8]);// wall8 corner down right
	else if (tile == 'W')
		return (arr[9]);// wall9 bush
	else if (tile == '1')
		return (arr[10]);// wall6 inside corner left
	else if (tile == 'A')
		return (arr[11]);// wall7 inside corner right
	else if (tile == 'B')
		return (arr[12]);// wall8 inside corner down left
	else if (tile == 'D')
		return (arr[13]);// wall9 inside corner down right
	else if (tile == 'H' || tile == 'P')
		return (arr[14]);// floor
	else if (tile == 'C')
		return (arr[15]);// collectible
	else if (tile == 'E')
		return (data->img->exit_tile);// exit
	else if (tile == '-')
		return (arr[15]);// door 
	else
		return (data->img->unknown_tile);// unknown
}

void	draw_map(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	if (data->cave)
	{
		while (data->map_cave[++i])
		{
			j = -1;
			while (data->map_cave[i][++j])
				mlx_put_image_to_window(data->mlx, data->win, draw_tile(data, data->map_cave[i][j], data->img->inside_tiles), j * 50, i * 50);
		}
	}
	else
	{
		while (data->map_copy[++i])
		{
			j = -1;
			while (data->map_copy[i][++j])
				mlx_put_image_to_window(data->mlx, data->win, draw_tile(data, data->map_copy[i][j], data->img->outside_tiles), j * 50, i * 50);
		}
	}
}


int	key_press(int keycode, t_data *data)
{
	int	x;
	int	y;

	x = data->player_possition[0];
	y = data->player_possition[1];
	if (data->map_copy[y][x] == '-')
	{
		
		if (data->cave)
			data->cave = 0;
		else
			data->cave = 1;
	}
	draw_map(data);
	if (data->map_copy[y][x] == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->img->exit_tile, x * 50, y * 50);
	else if (data->map_copy[y][x] == 'C')
	{
		data->map_copy[y][x] = 'H';
		data->collectible_nbr--;
		mlx_put_image_to_window(data->mlx, data->win, data->img->floor, data->player_possition[0] * 50, data->player_possition[1] * 50);
	}
	else
			mlx_put_image_to_window(data->mlx, data->win, data->img->floor, data->player_possition[0] * 50, data->player_possition[1] * 50);
	if (keycode == 13 || keycode == 126) // UP
	{
		if (data->map[y - 1][x] != '1' && data->map[y - 1][x] != '#')
			data->player_possition[1]--;
		mlx_put_image_to_window(data->mlx, data->win, data->img->exit_tile , data->player_possition[0] * 50, data->player_possition[1] * 50);
	}
	else if (keycode == 1 || keycode == 125) // down
	{
		if (data->map[y + 1][x] != '1' && data->map[y + 1][x] != '#')
			data->player_possition[1]++;
		mlx_put_image_to_window(data->mlx, data->win, data->img->exit_tile , data->player_possition[0] * 50, data->player_possition[1] * 50);
	}
	else if (keycode == 12 || keycode == 123) // left
	{
		if (data->map[y][x - 1] != '1' && data->map[y][x - 1] != '#')
			data->player_possition[0]--;
		mlx_put_image_to_window(data->mlx, data->win, data->img->exit_tile , data->player_possition[0] * 50, data->player_possition[1] * 50);
	}
	else if (keycode == 2 || keycode == 124) // right
	{
		if (data->map[y][x + 1] != '1' && data->map[y][x + 1] != '#')
			data->player_possition[0]++;
		mlx_put_image_to_window(data->mlx, data->win, data->img->exit_tile , data->player_possition[0] * 50, data->player_possition[1] * 50);
	}
	data->player_move_count++;
	if (data->map_copy[data->player_possition[1]][data->player_possition[0]] == 'E' && data->collectible_nbr == 0)
		printf("You win!\n");
	mlx_string_put(data->mlx, data->win, 5, 10, 136, "Move Count: ");
	mlx_string_put(data->mlx, data->win, 160, 10, 136, ft_itoa(data->player_move_count));
	mlx_string_put(data->mlx, data->win, 5, 25, 136, "Collected left: ");
	mlx_string_put(data->mlx, data->win, 160, 25, 136, ft_itoa(data->collectible_nbr));
	printf("player x: %d, y: %d\n", x, y);
	return (0);
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
	/*cave*/
	data->img->inside_tiles[0] = data->img->cave_wall_otop_corner_left;
	data->img->inside_tiles[1] = data->img->cave_wall_top;
	data->img->inside_tiles[2] = data->img->cave_wall_otop_corner_right;
	data->img->inside_tiles[3] = data->img->cave_wall_left;
	data->img->inside_tiles[4] = data->img->cave_wall_floor;
	data->img->inside_tiles[5] = data->img->cave_wall_right;
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
	/*player*/
	// data->img->player[0] = data->img->player_up;
	data->img->player[0][0] = data->img->player_up_0;
	data->img->player[0][1] = data->img->player_up_1;
	data->img->player[0][2] = data->img->player_up_2;
	data->img->player[0][3] = data->img->player_up_3;
	// data->img->player[1] = data->img->player_down;
	data->img->player[1][0] = data->img->player_down_0;
	data->img->player[1][1] = data->img->player_down_1;
	data->img->player[1][2] = data->img->player_down_2;
	data->img->player[1][3] = data->img->player_down_3;
	// data->img->player[2] = data->img->player_left;
	data->img->player[2][0] = data->img->player_left_0;
	data->img->player[2][1] = data->img->player_left_1;
	data->img->player[2][2] = data->img->player_left_2;
	data->img->player[2][3] = data->img->player_left_3;
	// data->img->player[3] = data->img->player_right;
	data->img->player[3][0] = data->img->player_right_0;
	data->img->player[3][1] = data->img->player_right_1;
	data->img->player[3][2] = data->img->player_right_2;
	data->img->player[3][3] = data->img->player_right_3;
}

void	start_game(t_data *data)
{
	printf("\x1b[1;32mSucces\x1b[0m\n");

	map_setup(data);
	print_map(data->map); // # X 1
	if (data->map_copy[data->player_possition[1]][data->player_possition[0]] == 'P')
		data->cave = 0;
	setting_mlx(data);
	load_image(data);
	image_setup(data);
	draw_map(data);
	mlx_hook(data->win, 2, 0, &key_press, data);
	// mlx_loop_hook(data->mlx, update_frame, data);
	mlx_loop(data->mlx);
}