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
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_win;
	t_data	*img;
	char *path = "./test.xpm";
	int		img_width;
	int		img_height;

	img = malloc(50);

	img_height = 1;
	img_width = 1;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 192, 108, "so_long");
	img->img = mlx_new_image(mlx, 192, 108);
	/*file to img*/
	img->img = mlx_xpm_file_to_image(mlx, path, &img_width, &img_height);
	if (!img)
		printf("ERROR\n");
	/*get img data*/
	//mg->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &(img->endian));
	/*put pixel to img*/
	// int x = -1;
	// while (++x < 40)
	// 	my_mlx_pixel_put(img, 5, 5 + x, 0x0000FF00);
	// /*put img to window*/
	mlx_put_image_to_window(mlx, mlx_win, img->img, 0, 0);
	mlx_loop(mlx);
	// printf("%s\n", av[0]);
	if (ac == 2)
	{
		printf("%s\n", av[1]);
	}
	else
		printf("Error no map!\n");
	mlx_destroy_window(mlx, mlx_win);
	free(mlx);
	return (0);
}
