/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:47:46 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/29 16:01:16 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_image_helper(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(data->mlx, data->img->player[3][i]);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(data->mlx, data->img->enemy[0][i]);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(data->mlx, data->img->enemy[1][i]);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(data->mlx, data->img->enemy[2][i]);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(data->mlx, data->img->enemy[3][i]);
	mlx_destroy_image(data->mlx, data->img->unknown_tile);
	mlx_destroy_image(data->mlx, data->img->exit_tile);
}

void	destroy_image(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 18)
		mlx_destroy_image(data->mlx, data->img->outside_tiles[i]);
	i = -1;
	while (++i < 18)
		mlx_destroy_image(data->mlx, data->img->inside_tiles[i]);
	i = -1;
	while (++i < 9)
		mlx_destroy_image(data->mlx, data->img->trap[i]);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(data->mlx, data->img->exit_on[i]);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(data->mlx, data->img->player[0][i]);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(data->mlx, data->img->player[1][i]);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(data->mlx, data->img->player[2][i]);
	destroy_image_helper(data);
}

void	load_image6(t_data *data)
{
	data->img->trap[7] = i("./data/texture/trap4.xpm", data);
	data->img->trap[8] = i("./data/texture/trap5.xpm", data);
	data->img->gui[0] = i("./data/texture/other/gui0.xpm", data);
	data->img->gui[1] = i("./data/texture/other/gui1.xpm", data);
	data->img->bar[0] = i("./data/texture/other/hp.xpm", data);
	data->img->bar[1] = i("./data/texture/other/rg.xpm", data);
	data->img_loaded = 1;
}

void	load_image5(t_data *data)
{
	data->img->enemy[0][0] = i("./data/texture/enemy/enemy_up0.xpm", data);
	data->img->enemy[0][1] = i("./data/texture/enemy/enemy_up1.xpm", data);
	data->img->enemy[0][2] = i("./data/texture/enemy/enemy_up2.xpm", data);
	data->img->enemy[0][3] = i("./data/texture/enemy/enemy_up1.xpm", data);
	data->img->enemy[1][0] = i("./data/texture/enemy/enemy_down0.xpm", data);
	data->img->enemy[1][1] = i("./data/texture/enemy/enemy_down1.xpm", data);
	data->img->enemy[1][2] = i("./data/texture/enemy/enemy_down2.xpm", data);
	data->img->enemy[1][3] = i("./data/texture/enemy/enemy_down1.xpm", data);
	data->img->enemy[3][0] = i("./data/texture/enemy/enemy_left0.xpm", data);
	data->img->enemy[3][1] = i("./data/texture/enemy/enemy_left1.xpm", data);
	data->img->enemy[3][2] = i("./data/texture/enemy/enemy_left2.xpm", data);
	data->img->enemy[3][3] = i("./data/texture/enemy/enemy_left1.xpm", data);
	data->img->enemy[2][0] = i("./data/texture/enemy/enemy_right0.xpm", data);
	data->img->enemy[2][1] = i("./data/texture/enemy/enemy_right1.xpm", data);
	data->img->enemy[2][2] = i("./data/texture/enemy/enemy_right2.xpm", data);
	data->img->enemy[2][3] = i("./data/texture/enemy/enemy_right1.xpm", data);
	data->img->trap[0] = i("./data/texture/trap0.xpm", data);
	data->img->trap[1] = i("./data/texture/trap0.xpm", data);
	data->img->trap[2] = i("./data/texture/trap0.xpm", data);
	data->img->trap[3] = i("./data/texture/trap0.xpm", data);
	data->img->trap[4] = i("./data/texture/trap1.xpm", data);
	data->img->trap[5] = i("./data/texture/trap2.xpm", data);
	data->img->trap[6] = i("./data/texture/trap3.xpm", data);
	load_image6(data);
}
