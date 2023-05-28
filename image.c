
#include "so_long.h"

void	load_image4(t_data *data)
{
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

void	load_image4(t_data *data)
{
	data->img->player[3][0] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyRight.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[3][1] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyRight1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[3][2] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyRight2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[3][3] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyRight3.xpm", &data->img->img_width, &data->img->img_height);
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
	load_image4(data);
}

void	load_image3(t_data *data)
{
	data->img->inside_tiles[11] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_itop_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[12] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_idown_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[13] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_idown_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[7] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_down.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[1] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_top.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[3] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[5] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[9] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_solo.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[17] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_door.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[1][0] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyDown.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[1][1] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyDown1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[1][2] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyDown2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[1][3] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyDown3.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[0][0] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyUp.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[0][1] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyUp1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[0][2] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyUp2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[0][3] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyUp3.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[2][0] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyLeft.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[2][1] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyLeft1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[2][2] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyLeft2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->player[2][3] = mlx_xpm_file_to_image(data->mlx, "./data/texture/player/fireflyLeft3.xpm", &data->img->img_width, &data->img->img_height);
	load_image4(data);
}

void	load_image2(t_data *data)
{
	data->img->outside_tiles[9] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_solo.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[17] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/door.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/portal.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile0 = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/portal_on0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile1 = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/portal_on1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile2 = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/portal_on2.xpm", &data->img->img_width, &data->img->img_height);
	data->img->exit_tile3 = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/portal_on3.xpm", &data->img->img_width, &data->img->img_height);
	data->img->unknown_tile = mlx_xpm_file_to_image(data->mlx, "./data/texture/other/unknown_tile.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[15] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_collectible0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[16] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_collectible1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[14] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_floor.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[4] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_floor.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[0] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_otop_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[2] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_otop_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[6] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_odown_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[8] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_odown_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->inside_tiles[10] = mlx_xpm_file_to_image(data->mlx, "./data/texture/cave/cave_wall_itop_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	load_image3(data);
}

void	load_image(t_data *data)
{
	data->img->outside_tiles[15] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/collectible0.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[16] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/collectible1.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[14] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/floor.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[4] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_floor.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[0] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_otop_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[2] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_otop_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[6] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_odown_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[8] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_odown_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[10] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_itop_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[11] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_itop_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[12] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_idown_corner_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[13] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_idown_corner_right.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[7] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_down.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[1] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_top.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[3] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_left.xpm", &data->img->img_width, &data->img->img_height);
	data->img->outside_tiles[5] = mlx_xpm_file_to_image(data->mlx, "./data/texture/outside/wall_right.xpm", &data->img->img_width, &data->img->img_height);
	load_image2(data);
}
