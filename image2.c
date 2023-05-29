/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:47:46 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/29 13:44:11 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_image6(t_data *data)
{
	data->img->trap[7] = i("./data/texture/trap4.xpm", data);
	data->img->trap[8] = i("./data/texture/trap5.xpm", data);
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
