#include "so_long.h"

#include <stdlib.h>
#include <stdio.h>

int get_len(int nbr)
{
    int len = 0;
    while (nbr != 0)
    {
        len++;
        nbr /= 10;
    }
    return (len);
}

char *ft_itoa(int nbr)
{
    char *str;
    int i = get_len(nbr);
    if (nbr <= 0)
        i++;

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
    str[i] = '\0';

    i--;
    if (nbr == 0)
        str[i] = '0';
    while (nbr != 0)
    {
        str[i--] = nbr % 10 + '0';
        nbr /= 10;
    }
    return (str);
}

#define TARGET_FPS 60

int previous_frame_time = 0;
void draw_frame() {
    // Your code to draw a single frame
}
int update_frame() {
    int current_time = mlx_get_time();
    int elapsed_time = current_time - previous_frame_time;
    int target_frame_time = 1000 / TARGET_FPS;
    if (elapsed_time >= target_frame_time) {
        draw_frame();
        previous_frame_time = current_time;
    }
    return 0;
}


int	key_press(int keycode, t_data *data)
{
	int	x;
	int	y;

	x = data->player_possition[0];
	y = data->player_possition[1];
	if (data->map_copy[y][x] == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->exit_tile, x * 50, y * 50);
	else if (data->map_copy[y][x] == 'C')
	{
		data->map_copy[y][x] = '0';
		data->collectible_nbr--;
	}
	else
		mlx_put_image_to_window(data->mlx, data->win, data->floor, x * 50, y * 50);
	if (keycode == 13 || keycode == 126) // UP
	{
		mlx_put_image_to_window(data->mlx, data->win, data->playerUp , x * 50, y * 50);
		if (data->map_copy[y - 1][x] != '1')
			data->player_possition[1]--;
	}
	else if (keycode == 1 || keycode == 125) // down
	{
		mlx_put_image_to_window(data->mlx, data->win, data->playerDown , x * 50, y * 50);
		if (data->map_copy[y + 1][x] != '1')
			data->player_possition[1]++;
	}
	else if (keycode == 12 || keycode == 123) // left
	{
		mlx_put_image_to_window(data->mlx, data->win, data->playerLeft , x * 50, y * 50);
		if (data->map_copy[y][x - 1] != '1')
			data->player_possition[0]--;
	}
	else if (keycode == 2 || keycode == 124) // right
	{
		mlx_put_image_to_window(data->mlx, data->win, data->playerRight , x * 50, y * 50);
		if (data->map_copy[y][x + 1] != '1')
			data->player_possition[0]++;
	}
	data->player_move_count++;
	if (data->map_copy[y][x] == 'E' && data->collectible_nbr == 0)
		printf("You win!\n");
	mlx_string_put(data->mlx, data->win, 5, 10, 136, "Move Count: ");
	mlx_string_put(data->mlx, data->win, 20, 10, 136, ft_itoa(data->player_move_count));
	mlx_string_put(data->mlx, data->win, 5, 10, 136, "Collected left: ");
	mlx_string_put(data->mlx, data->win, 20, 10, 136, ft_itoa(data->collectible_nbr));
	mlx_put_image_to_window(data->mlx, data->wall, data->player_image, 0 * 50, 0 * 50);
	mlx_put_image_to_window(data->mlx, data->wall, data->player_image, 1 * 50, 0 * 50);
	printf("player x: %d, y: %d\n", x, y);
	return (0);
}

void	setting_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 50 * data->map_width, 50 * data->map_height, "The Mysterious Firefly Cave");
}

void	load_image(t_data *data)
{
	data->floor = mlx_xpm_file_to_image(data->mlx, "./data/texture/floor.xpm", &data->map_width, &data->map_height);
	data->wall = mlx_xpm_file_to_image(data->mlx, "./data/texture/wall.xpm", &data->map_width, &data->map_height);
	data->wall0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/wall0.xpm", &data->map_width, &data->map_height);
	data->wall1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/wall1.xpm", &data->map_width, &data->map_height);
	data->wall2 = mlx_xpm_file_to_image(data->mlx, "./data/texture/wall2.xpm", &data->map_width, &data->map_height);
	data->wall3 = mlx_xpm_file_to_image(data->mlx, "./data/texture/wall3.xpm", &data->map_width, &data->map_height);
	data->wallTop = mlx_xpm_file_to_image(data->mlx, "./data/texture/walltop.xpm", &data->map_width, &data->map_height);
	data->wallLeft = mlx_xpm_file_to_image(data->mlx, "./data/texture/wallleft.xpm", &data->map_width, &data->map_height);
	data->wallRight = mlx_xpm_file_to_image(data->mlx, "./data/texture/wallright.xpm", &data->map_width, &data->map_height);
	data->coll = mlx_xpm_file_to_image(data->mlx, "./data/texture/collectible.xpm", &data->map_width, &data->map_height);
	data->exit_tile = mlx_xpm_file_to_image(data->mlx, "./data/texture/exit.xpm", &data->map_width, &data->map_height);
	data->playerUp = mlx_xpm_file_to_image(data->mlx, "./data/texture/fireflyUp.xpm", &data->map_width, &data->map_height);
	data->playerDown = mlx_xpm_file_to_image(data->mlx, "./data/texture/fireflyDown.xpm", &data->map_width, &data->map_height);
	data->playerLeft = mlx_xpm_file_to_image(data->mlx, "./data/texture/fireflyLeft.xpm", &data->map_width, &data->map_height);
	data->playerRight = mlx_xpm_file_to_image(data->mlx, "./data/texture/fireflyRight.xpm", &data->map_width, &data->map_height);
}

void	setting_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map_copy[++i])
	{
		j = -1;
		while (data->map_copy[i][++j])
		{
			if (data->map_copy[i][j] == '1')
			{
				if (data->map_copy[i - 1][j] && data->map_copy[i - 1][j] != '1')
					mlx_put_image_to_window(data->mlx, data->win, data->wallTop, j * 50, i * 50);
				else if (data->map_copy[i + 1][j] && data->map_copy[i + 1][j] != '1')
					mlx_put_image_to_window(data->mlx, data->win, data->wall, j * 50, i * 50);
				else if (data->map_copy[1][j - 1] && data->map_copy[1][j - 1] != '1')
					mlx_put_image_to_window(data->mlx, data->win, data->wallLeft, j * 50, i * 50);
				else if (data->map_copy[1][j + 1] && data->map_copy[1][j + 1] != '1')
					mlx_put_image_to_window(data->mlx, data->win, data->wallRight, j * 50, i * 50);
				else
					mlx_put_image_to_window(data->mlx, data->win, data->wall0, j * 50, i * 50);
			}
			else if (data->map_copy[i][j] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->coll, j * 50, i * 50);
			else if (data->map_copy[i][j] == 'P')
				mlx_put_image_to_window(data->mlx, data->win, data->playerUp, j * 50, i * 50);
			else if (data->map_copy[i][j] == '0')
				mlx_put_image_to_window(data->mlx, data->win, data->floor, j * 50, i * 50);
			else if (data->map_copy[i][j] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->exit_tile, j * 50, i * 50);
		}
	}
}

void	start_game(t_data *data)
{
	data->player_move_count = 0;
	data->collected_count = 0;
	setting_mlx(data);
	load_image(data);
	setting_map(data);
	mlx_hook(data->win, 2, 0, &key_press, data);
	mlx_loop_hook(data->mlx, update_frame, NULL);
	mlx_loop(data->mlx);
}
