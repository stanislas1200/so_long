/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:46:39 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/20 17:39:46 by sgodin           ###   ########.fr       */
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

int	update_frame(t_data *data)
{
	if (data->time >= 1000)
		data->time = 0;
	if (data->cave)
		mlx_put_image_to_window(data->mlx, data->win, data->img->cave_floor, \
		data->player_possition[0] * 50, data->player_possition[1] * 50);
	else
		mlx_put_image_to_window(data->mlx, data->win, data->img->floor, \
		data->player_possition[0] * 50, data->player_possition[1] * 50);
	mlx_put_image_to_window(data->mlx, data->win, data->img->\
	player[data->direction][(data->time / 10) % 4], data->player_possition[0] * \
	50, data->player_possition[1] * 50);
	data->time++;
	return (0);
}

void	setting_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 50 * data->map_width, 50 * \
	data->map_height, "The Mysterious Firefly Cave");
}

void	load_image4(t_data *data)
{
	data->img->player_right_0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/\
	player/fireflyRight.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_right_1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/\
	player/fireflyRight1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_right_2 = mlx_xpm_file_to_image(data->mlx, "./data/texture/\
	player/fireflyRight2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_right_3 = mlx_xpm_file_to_image(data->mlx, "./data/texture/\
	player/fireflyRight3.xpm", &data->img->img_width, &data->img->img_height);
}

void	laod_image3(t_data *data)
{
	data->img->cave_wall_itop_corner_right = mlx_xpm_file_to_image(data->mlx, "./\
	data/texture/cave/cave_wall_itop_corner_right.xpm", &data->img->img_width, \
	&data->img->img_height);
	data->img->cave_wall_idown_corner_left = mlx_xpm_file_to_image(data->mlx, "./\
	data/texture/cave/cave_wall_idown_corner_left.xpm", &data->img->img_width, \
	&data->img->img_height);
	data->img->cave_wall_idown_corner_right = mlx_xpm_file_to_image(data->mlx, ".\
	/data/texture/cave/cave_wall_idown_corner_right.xpm", &data->img->img_width \
	, &data->img->img_height);
	data->img->cave_wall_down = mlx_xpm_file_to_image(data->mlx, "./data/texture/\
	cave/cave_wall_down.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_top = mlx_xpm_file_to_image(data->mlx, "./data/texture/c\
	ave/cave_wall_top.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_left = mlx_xpm_file_to_image(data->mlx, "./data/texture/\
	cave/cave_wall_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_right = mlx_xpm_file_to_image(data->mlx, "./data/texture\
	/cave/cave_wall_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_solo = mlx_xpm_file_to_image(data->mlx, "./data/texture/\
	cave/cave_wall_solo.xpm", &data->img->img_width, &data->img->img_height);
	data->img->door = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/door.\
	xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_down_0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/p\
	layer/fireflyDown.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_down_1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/p\
	layer/fireflyDown1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_down_2 = mlx_xpm_file_to_image(data->mlx, "./data/texture/p\
	layer/fireflyDown2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_down_3 = mlx_xpm_file_to_image(data->mlx, "./data/texture/p\
	layer/fireflyDown3.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_up_0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/pla\
	yer/fireflyUp.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_up_1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/pla\
	yer/fireflyUp1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_up_2 = mlx_xpm_file_to_image(data->mlx, "./data/texture/pla\
	yer/fireflyUp2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_up_3 = mlx_xpm_file_to_image(data->mlx, "./data/texture/pla\
	yer/fireflyUp3.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_left_0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/p\
	layer/fireflyLeft.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_left_1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/p\
	layer/fireflyLeft1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_left_2 = mlx_xpm_file_to_image(data->mlx, "./data/texture/p\
	layer/fireflyLeft2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player_left_3 = mlx_xpm_file_to_image(data->mlx, "./data/texture/p\
	layer/fireflyLeft3.xpm", &data->img->img_width, &data->img->img_height);
	load_image4(data);
}

void	load_image2(t_data *data)
{
	data->img->wall_solo = mlx_xpm_file_to_image(data->mlx, "./data/texture/outsi\
	de/wall_solo.xpm", &data->img->img_width, &data->img->img_height);
	data->img->door = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/do\
	or.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile = mlx_xpm_file_to_image(data->mlx, "./data/texture/other\
	/portal.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/othe\
	r/portal_on0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/othe\
	r/portal_on1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile2 = mlx_xpm_file_to_image(data->mlx, "./data/texture/othe\
	\
	r/portal_on2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile3 = mlx_xpm_file_to_image(data->mlx, "./data/texture/othe\
	r/portal_on3.xpm", &data->img->img_width, &data->img->img_height);
	data->img->unknown_tile = mlx_xpm_file_to_image(data->mlx, "./data/texture/ot\
	her/unknown_tile.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_collectible0 = mlx_xpm_file_to_image(data->mlx, "./data/textu\
	re/cave/cave_collectible0.xpm", &data->img->img_width, \
	&data->img->img_height);
	data->img->cave_collectible1 = mlx_xpm_file_to_image(data->mlx, "./data/textur\
	e/cave/cave_collectible1.xpm", &data->img->img_width, \
	&data->img->img_height);
	data->img->cave_floor = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave\
	/cave_floor.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_floor = mlx_xpm_file_to_image(data->mlx, "./data/texture\
	/cave/cave_wall_floor.xpm", &data->img->img_width, &data->img->img_height);
	data->img->cave_wall_otop_corner_left = mlx_xpm_file_to_image(data->mlx, "./d\
	ata/texture/cave/cave_wall_otop_corner_left.xpm", &data->img->img_width, \
	&data->img->img_height);
	data->img->cave_wall_otop_corner_right = mlx_xpm_file_to_image(data->mlx, "./\
	data/texture/cave/cave_wall_otop_corner_right.xpm", &data->img->img_width, \
	&data->img->img_height);
	data->img->cave_wall_odown_corner_left = mlx_xpm_file_to_image(data->mlx, "./\
	data/texture/cave/cave_wall_odown_corner_left.xpm", &data->img->img_width, \
	&data->img->img_height);
	data->img->cave_wall_odown_corner_right = mlx_xpm_file_to_image(data->mlx, ".\
	/data/texture/cave/cave_wall_odown_corner_right.xpm", &data->img->img_width \
	, &data->img->img_height);
	data->img->cave_wall_itop_corner_left = mlx_xpm_file_to_image(data->mlx, "./d\
	ata/texture/cave/cave_wall_itop_corner_left.xpm", &data->img->img_width, \
	&data->img->img_height);
	load_image3(data);
}

void	load_image(t_data *data)
{
	data->img->collectible0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/\
	outside/collectible0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->collectible1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/\
	outside/collectible1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->floor = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside\
	/floor.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_floor = mlx_xpm_file_to_image(data->mlx, "./data/texture/ou\
	tside/wall_floor.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_otop_corner_left = mlx_xpm_file_to_image(data->mlx, "./data\
	/texture/outside/wall_otop_corner_left.xpm", &data->img->img_width, &data->\
	img->img_height);
	data->img->wall_otop_corner_right = mlx_xpm_file_to_image(data->mlx, "./data\
	/texture/outside/wall_otop_corner_right.xpm", &data->img->img_width, &data->\
	img->img_height);
	data->img->wall_odown_corner_left = mlx_xpm_file_to_image(data->mlx, "./data\
	/texture/outside/wall_odown_corner_left.xpm", &data->img->img_width, &data->\
	img->img_height);
	data->img->wall_odown_corner_right = mlx_xpm_file_to_image(data->mlx, "./dat\
	a/texture/outside/wall_odown_corner_right.xpm", &data->img->img_width, \
	&data->img->img_height);
	data->img->wall_itop_corner_left = mlx_xpm_file_to_image(data->mlx, "./data/\
	texture/outside/wall_itop_corner_left.xpm", &data->img->img_width, &data->\
	img->img_height);
	data->img->wall_itop_corner_right = mlx_xpm_file_to_image(data->mlx, "./data\
	/texture/outside/wall_itop_corner_right.xpm", &data->img->img_width, &data->\
	img->img_height);
	data->img->wall_idown_corner_left = mlx_xpm_file_to_image(data->mlx, "./data\
	/texture/outside/wall_idown_corner_left.xpm", &data->img->img_width, &data->\
	img->img_height);
	data->img->wall_idown_corner_right = mlx_xpm_file_to_image(data->mlx, "./data\
	/texture/outside/wall_idown_corner_right.xpm", &data->img->img_width, \
	&data->img->img_height);
	data->img->wall_down = mlx_xpm_file_to_image(data->mlx, "./data/texture/outsi\
	de/wall_down.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_top = mlx_xpm_file_to_image(data->mlx, "./data/texture/outsid\
	e/wall_top.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_left = mlx_xpm_file_to_image(data->mlx, "./data/texture/outsi\
	de/wall_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->wall_right = mlx_xpm_file_to_image(data->mlx, "./data/texture/outs\
	ide/wall_right.xpm", &data->img->img_width, &data->img->img_height);
	load_image2(data);
}

void	*get_tile_helper(t_data *data, char tile, void **arr)
{
	if (tile == 'A')
		return (arr[11]);
	else if (tile == 'B')
		return (arr[12]);
	else if (tile == 'D')
		return (arr[13]);
	else if (tile == 'H' || tile == 'P')
		return (arr[14]);
	else if (tile == 'C')
	{
		if ((data->time / 10) % 2)
			return (arr[15]);
		return (arr[16]);
	}
	else if (tile == 'E')
		return (data->img->exit_tile);
	else if (tile == '-')
		return (arr[17]);
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
void	*get_tile(t_data *data, char tile, void **arr)
{
	if (tile == '2')
		return (arr[0]);
	else if (tile == '3')
		return (arr[1]);
	else if (tile == '4')
		return (arr[2]);
	else if (tile == '0')
		return (arr[3]);
	else if (tile == '5')
		return (arr[4]);
	else if (tile == '6')
		return (arr[5]);
	else if (tile == '7')
		return (arr[6]);
	else if (tile == '8')
		return (arr[7]);
	else if (tile == '9')
		return (arr[8]);
	else if (tile == 'W')
		return (arr[9]);
	else if (tile == '1')
		return (arr[10]);
	else
		return (get_tile_helper(data, tile, arr));
}

void	draw_map_helper(t_data *data, void ***ptr, void **arr)
{
	int		i;
	int		j;
	void	*img;

	i = -1;
	while ((*ptr)[++i])
	{
		j = -1;
		while ((*ptr)[i][++j])
		{
			img = get_tile(data, (*ptr)[i][j], arr);
			if (!img)
				mlx_put_image_to_window(data->mlx, data->win, \
				data->img->unknown_tile, j * 50, i * 50);
			else
				mlx_put_image_to_window(data->mlx, data->win, img, \
				j * 50, i * 50);
		}
	}
}

void	draw_map(t_data *data)
{
	void	***ptr;
	void	**arr;

	if (data->cave)
	{
		ptr = &data->map_cave;
		arr = data->img->inside_tiles;
	}
	else
	{
		ptr = &data->map_copy;
		arr = data->img->outside_tiles;
	}
	draw_map_helper(data, ptr, arr);
}

void	print_on_screen(t_data *data)
{
	// make to store then free ?
	mlx_string_put(data->mlx, data->win, 5, 10, 136, "Move Count: ");
	mlx_string_put(data->mlx, data->win, 160, \
	10, 136, ft_itoa(data->player_move_count));
	mlx_string_put(data->mlx, data->win, 5, 25, 136, "Collected left: ");
	mlx_string_put(data->mlx, data->win, 160, \
	25, 136, ft_itoa(data->collectible_nbr));
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
	mlx_put_image_to_window(data->mlx, data->win, data->img->\
	player[data->direction][(data->time / 10) % 4], \
	data->player_possition[0] * 50, data->player_possition[1] * 50);
}

void	do_tile_action(t_data *data, char ****ptr)
{
	if ((*ptr)[data->player_possition[1]][data->player_possition[0]] == 'C')
	{
		(*ptr)[data->player_possition[1]][data->player_possition[0]] = 'H';
		data->collectible_nbr--;
	}
	else if ((*ptr)[data->player_possition[1]][data->player_possition[0]] \
	== '-')
	{
		if (data->cave)
		{
			data->cave = 0;
			data->player_possition[0] = data->player_possition[0] - 1;
		}
		else
		{
			data->cave = 1;
			data->player_possition[0] = data->player_possition[0] + 1;
		}
		draw_map(data);
	}
	else if ((*ptr)[data->player_possition[1]][data->player_possition[0]] \
	== 'E' && data->collectible_nbr == 0)
		printf("You win!\n");
}

int	key_press(int keycode, t_data *data)
{
	char	***ptr;
	void	**arr;

	if (data->cave)
	{
		ptr = &data->map_cave;
		arr = data->img->inside_tiles;
	}
	else
	{
		ptr = &data->map_copy;
		arr = data->img->outside_tiles;
	}
	mlx_put_image_to_window(data->mlx, data->win, \
	get_tile(data, (*ptr)[data->player_possition[1]][data->player_possition[0]] \
	, arr), data->player_possition[1] * 50, data->player_possition[0] * 50);
	move_player(keycode, data, data->map);
	do_tile_action(data, ptr);
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
	draw_map(data);
	mlx_hook(data->win, 2, 0, &key_press, data);
	mlx_loop_hook(data->mlx, update_frame, data);
	mlx_loop(data->mlx);
}
