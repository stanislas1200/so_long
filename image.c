
#include "so_long.h"

void	*i(char *str, t_data *data)
{
	return (mlx_xpm_file_to_image(data->mlx, str, \
	&data->img->img_width, &data->img->img_height));
}

void	load_image5(t_data *data)
{
	data->img->trap[4] = i("./data/texture/trap1.xpm", data);
	data->img->trap[5] = i("./data/texture/trap2.xpm", data);
	data->img->trap[6] = i("./data/texture/trap3.xpm", data);
	data->img->trap[7] = i("./data/texture/trap4.xpm", data);
	data->img->trap[8] = i("./data/texture/trap5.xpm", data);
	data->img->exit_on[0] = i("./data/texture/other/portal_on0.xpm", data);
	data->img->exit_on[1] = i("./data/texture/other/portal_on1.xpm", data);
	data->img->exit_on[2] = i("./data/texture/other/portal_on2.xpm", data);
	data->img->exit_on[3] = i("./data/texture/other/portal_on3.xpm", data);
}

void	load_image4(t_data *data)
{
	data->img->player[3][0] = i("./data/texture/player/fireflyRight.xpm", data);
	data->img->player[3][1] = i("./data/texture/player/fireflyRight1.xpm", data);
	data->img->player[3][2] = i("./data/texture/player/fireflyRight2.xpm", data);
	data->img->player[3][3] = i("./data/texture/player/fireflyRight3.xpm", data);
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
	load_image5(data);
}

void	load_image3(t_data *data)
{
	data->img->inside_tiles[11] = i("./data/texture/cave/cave_wall_itop_corner_right.xpm", data);
	data->img->inside_tiles[12] = i("./data/texture/cave/cave_wall_idown_corner_left.xpm", data);
	data->img->inside_tiles[13] = i("./data/texture/cave/cave_wall_idown_corner_right.xpm", data);
	data->img->inside_tiles[7] = i("./data/texture/cave/cave_wall_down.xpm", data);
	data->img->inside_tiles[1] = i("./data/texture/cave/cave_wall_top.xpm", data);
	data->img->inside_tiles[3] = i("./data/texture/cave/cave_wall_left.xpm", data);
	data->img->inside_tiles[5] = i("./data/texture/cave/cave_wall_right.xpm", data);
	data->img->inside_tiles[9] = i("./data/texture/cave/cave_wall_solo.xpm", data);
	data->img->inside_tiles[17] = i("./data/texture/cave/cave_door.xpm", data);
	data->img->player[1][0] = i("./data/texture/player/fireflyDown.xpm", data);
	data->img->player[1][1] = i("./data/texture/player/fireflyDown1.xpm", data);
	data->img->player[1][2] = i("./data/texture/player/fireflyDown2.xpm", data);
	data->img->player[1][3] = i("./data/texture/player/fireflyDown3.xpm", data);
	data->img->player[0][0] = i("./data/texture/player/fireflyUp.xpm", data);
	data->img->player[0][1] = i("./data/texture/player/fireflyUp1.xpm", data);
	data->img->player[0][2] = i("./data/texture/player/fireflyUp2.xpm", data);
	data->img->player[0][3] = i("./data/texture/player/fireflyUp3.xpm", data);
	data->img->player[2][0] = i("./data/texture/player/fireflyLeft.xpm", data);
	data->img->player[2][1] = i("./data/texture/player/fireflyLeft1.xpm", data);
	data->img->player[2][2] = i("./data/texture/player/fireflyLeft2.xpm", data);
	data->img->player[2][3] = i("./data/texture/player/fireflyLeft3.xpm", data);
	load_image4(data);
}

void	load_image2(t_data *data)
{
	data->img->outside_tiles[9] = i("./data/texture/outside/wall_solo.xpm", data);
	data->img->outside_tiles[17] = i("./data/texture/outside/door.xpm", data);
	data->img->exit_tile = i("./data/texture/other/portal.xpm", data);
	data->img->exit_tile0 = i("./data/texture/other/portal_on0.xpm", data);
	data->img->exit_tile1 = i("./data/texture/other/portal_on1.xpm", data);
	data->img->exit_tile2 = i("./data/texture/other/portal_on2.xpm", data);
	data->img->exit_tile3 = i("./data/texture/other/portal_on3.xpm", data);
	data->img->unknown_tile = i("./data/texture/other/unknown_tile.xpm", data);
	data->img->inside_tiles[15] = i("./data/texture/cave/cave_collectible0.xpm", data);
	data->img->inside_tiles[16] = i("./data/texture/cave/cave_collectible1.xpm", data);
	data->img->inside_tiles[14] = i("./data/texture/cave/cave_floor.xpm", data);
	data->img->inside_tiles[4] = i("./data/texture/cave/cave_wall_floor.xpm", data);
	data->img->inside_tiles[0] = i("./data/texture/cave/cave_wall_otop_corner_left.xpm", data);
	data->img->inside_tiles[2] = i("./data/texture/cave/cave_wall_otop_corner_right.xpm", data);
	data->img->inside_tiles[6] = i("./data/texture/cave/cave_wall_odown_corner_left.xpm", data);
	data->img->inside_tiles[8] = i("./data/texture/cave/cave_wall_odown_corner_right.xpm", data);
	data->img->inside_tiles[10] = i("./data/texture/cave/cave_wall_itop_corner_left.xpm", data);
	load_image3(data);
}

void	load_image(t_data *data)
{
	data->img->outside_tiles[15] = i("./data/texture/outside/collectible0.xpm", data);
	data->img->outside_tiles[16] = i("./data/texture/outside/collectible1.xpm", data);
	data->img->outside_tiles[14] = i("./data/texture/outside/floor.xpm", data);
	data->img->outside_tiles[4] = i("./data/texture/outside/wall_floor.xpm", data);
	data->img->outside_tiles[0] = i("./data/texture/outside/wall_otop_corner_left.xpm", data);
	data->img->outside_tiles[2] = i("./data/texture/outside/wall_otop_corner_right.xpm", data);
	data->img->outside_tiles[6] = i("./data/texture/outside/wall_odown_corner_left.xpm", data);
	data->img->outside_tiles[8] = i("./data/texture/outside/wall_odown_corner_right.xpm", data);
	data->img->outside_tiles[10] = i("./data/texture/outside/wall_itop_corner_left.xpm", data);
	data->img->outside_tiles[11] = i("./data/texture/outside/wall_itop_corner_right.xpm", data);
	data->img->outside_tiles[12] = i("./data/texture/outside/wall_idown_corner_left.xpm", data);
	data->img->outside_tiles[13] = i("./data/texture/outside/wall_idown_corner_right.xpm", data);
	data->img->outside_tiles[7] = i("./data/texture/outside/wall_down.xpm", data);
	data->img->outside_tiles[1] = i("./data/texture/outside/wall_top.xpm", data);
	data->img->outside_tiles[3] = i("./data/texture/outside/wall_left.xpm", data);
	data->img->outside_tiles[5] = i("./data/texture/outside/wall_right.xpm", data);
	load_image2(data);
}
