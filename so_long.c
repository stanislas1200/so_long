/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:59:20 by sgodin            #+#    #+#             */
/*   Updated: 2023/04/26 17:02:41 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	**map;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

char **split_lines(char *all_line, int len)
{
    int i;
	int j;
	int tab_size;
    char **tab;

	i = 0;
	tab_size = 0;
	while (all_line[i])
	{
		if (all_line[i] == '\n')
			tab_size++;
		i++;
	}
	tab = malloc(sizeof(char *) * (tab_size + 2));
	if (!tab)
		return (NULL);
	i = 0;
	tab[tab_size + 1] = NULL;
	j = 0;
	tab[i] = malloc(sizeof(char) * len + 2); 
	while (*all_line)
	{
		tab[i][j++] = *all_line++;
		if (*all_line == '\n')
		{
			tab[i][j] = '\0';
			i++;
			j = 0;
			tab[i] = malloc(sizeof(char) * len + 2);
			all_line++;
		}
	}
    return tab;
}

/*Check the map file and set the map*/
void	check_map(char *path, char ***map, t_data *data)
{
	int		i;
	int		j;
	int		k;
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		char *new_path;
		new_path = ft_strjoin("./data/map/", path);
		fd = open(new_path, O_RDONLY);
		free(new_path);
		if (fd == -1)
		{
			perror("\x1b[1;31mError\x1b[0m");
			free(data);
			exit(1);
		}
	}

	char *line = NULL;
	char *all_line;
	char* tmp = NULL;
	line = get_next_line(fd);
	if (!line)
	{
		printf("\x1b[1;31mError \x1b[0m: Map is empty !\n");
		free(data);
		exit(1);
	}
	i = ft_strlen(line);
	j = 0;
	all_line = ft_strjoin("", line);
	while (line)
	{
		k = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
		if (!line)
			i -= 2;
		else {
			tmp = ft_strjoin(all_line, line);
			free(all_line);
			all_line = tmp;
			}
		if (i != k)
		{
			printf("\x1b[1;31mError \x1b[0m: Map line \x1b[1;35m%d and %d\x1b[0m doesn't have the same lenght !\n", j - 1, j - 2);
			free(all_line);
			free(data);
			exit(1);
		}
		
		j++;
	}
	printf("\nAll line : \n%s\n", all_line);
	*map = split_lines(all_line, i);
	free(all_line);
}

int	main(int ac, char **av)
{
	// void	*mlx;
	// void	*mlx_win;
	t_data	*data;
	// char *path = "./test.xpm";
	// int		img_width;
	// int		img_height;

	data = malloc(sizeof(t_data));

	// img_height = 1;
	// img_width = 1;

	/*init mlx*/
	// mlx = mlx_init();
	/*create window*/
	// mlx_win = mlx_new_window(mlx, 192, 108, "so_long");

	// img->img = mlx_new_image(mlx, 192, 108);
	// /*file to img*/
	// if (!img)
	// 	printf("ERROR\n");
	// /*get img data*/
	// //mg->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &(img->endian));
	// /*put pixel to img*/
	// // int x = -1;
	// // while (++x < 40)
	// // 	my_mlx_pixel_put(img, 5, 5 + x, 0x0000FF00);

	/*Get Image from file*/
	// data->img = mlx_xpm_file_to_image(mlx, "floor.xpm", &img_width, &img_height);
	/*Put img to window*/
	// mlx_put_image_to_window(mlx, mlx_win, data->img, 20, 20);
	/*Loop*/
	// mlx_loop(mlx);

	// // printf("%s\n", av[0]);
	if (ac == 2)
	{
		check_map(av[1], &data->map, data);
	}
	else
		printf("\x1b[33mWarning :\x1b[0m No Map!\n");
	// mlx_destroy_window(mlx, mlx_win);
	// free(mlx);
	int i = 0;
	while(data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	free(data);
	return (0);
}


/*Image*/

// int main()
// {
// 		void *mlx;
// 		void *win;
// 		void *img;

// 		int		img_width;
// 		int 	img_height;

// 		mlx = mlx_init();
// 		win = mlx_new_window(mlx, 500, 500, "my_mlx");
// 		img = mlx_xpm_file_to_image(mlx, "../textures/wall_n.xpm", &img_width, &img_height);
// 		mlx_put_image_to_window(mlx, win, img, 50, 50);
// 		mlx_loop(mlx);
// 		return (0);
// }



/*Keys*/

// #define X_EVENT_KEY_PRESS		2
// #define X_EVENT_KEY_release		3
// #define X_EVENT_KEY_EXIT		17 //exit key code

// //Mac key code example
// //All the key code example other than below is described on the site linked in READEME.md
// #define KEY_ESC			53
// # define KEY_Q			12
// # define KEY_W			13
// # define KEY_E			14
// # define KEY_R			15
// # define KEY_A			0
// # define KEY_S			1
// # define KEY_D			2

// //Since key_press() can recieve only one argument, all the argument shold be gathered in one structure
// //x,y and str are meaningless variables.
// typedef struct s_param{
// 	int		x;
// 	int		y;
// 	char	str[3];
// }				t_param;

// //Only param->x will be used. 
// void			param_init(t_param *param)
// {
// 	param->x = 3;
// 	param->y = 4;
// 	param->str[0] = 'a';
// 	param->str[1] = 'b';
// 	param->str[2] = '\0';
// }

// int				key_press(int keycode, t_param *param)
// {
// 	static int a = 0;

// 	if (keycode == KEY_W)//Action when W key pressed
// 		param->x++;
// 	else if (keycode == KEY_S) //Action when S key pressed
// 		param->x--;
// 	else if (keycode == KEY_ESC) //Quit the program when ESC key pressed
// 		exit(0);
// 	printf("x: %d\n", param->x);
// 	return (0);
// }

// int			main(void)
// {
// 	void		*mlx;
// 	void		*win;
// 	t_param		param;

// 	param_init(&param);
// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, 500, 500, "mlx_project");
// 	printf("-------------------------------\n");
// 	printf("'W key': Add 1 to x.\n");
// 	printf("'S key': Subtract 1 from x\n");
// 	printf("'ESC key': Exit this program\n");
// 	printf("'Other keys': print current x \n");
// 	printf("-------------------------------\n");
// 	printf("Current x = 3\n");
// 	mlx_hook(win, X_EVENT_KEY_PRESS, 0, &key_press, &param);
// 	mlx_loop(mlx);
// }