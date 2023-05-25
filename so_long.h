/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:59:33 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/25 12:36:51 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include "get_next_line.h"
# include <fcntl.h>

# include <string.h>

typedef struct s_img
{
	int		img_width;
	int		img_height;
	void	**exit_on[4];
	void	*exit_tile;
	void	*exit_tile0;
	void	*exit_tile1;
	void	*exit_tile2;
	void	*exit_tile3;
	void	*unknown_tile;
	/*outside*/
	void	*outside_tiles[18];
	void	*floor;
	void	*wall_floor;
	void	*wall_otop_corner_left;
	void	*wall_otop_corner_right;
	void	*wall_odown_corner_left;
	void	*wall_odown_corner_right;
	void	*wall_itop_corner_left;
	void	*wall_itop_corner_right;
	void	*wall_idown_corner_left;
	void	*wall_idown_corner_right;
	void	*wall_left;
	void	*wall_right;
	void	*wall_down;
	void	*wall_top;
	void	*wall_solo;
	void	*door;
	void	*collectible0;
	void	*collectible1;
	/*cave*/
	void	*inside_tiles[18];
	void	*cave_floor;
	void	*cave_wall_floor;
	void	*cave_wall_otop_corner_left;
	void	*cave_wall_otop_corner_right;
	void	*cave_wall_odown_corner_left;
	void	*cave_wall_odown_corner_right;
	void	*cave_wall_itop_corner_left;
	void	*cave_wall_itop_corner_right;
	void	*cave_wall_idown_corner_left;
	void	*cave_wall_idown_corner_right;
	void	*cave_wall_left;
	void	*cave_wall_right;
	void	*cave_wall_down;
	void	*cave_wall_top;
	void	*cave_wall_solo;
	void	*cave_door;
	void	*cave_collectible0;
	void	*cave_collectible1;
	/*---*/
	/*trap*/
	void	**trap[6];
	/*player*/
	void	**player[5][5];
	/*enemy*/
	void	*enemy_right_0;
	// void	*player_up[5];
	void	*player_up_0;
	void	*player_up_1;
	void	*player_up_2;
	void	*player_up_3;
	// void	*player_down[5];
	void	*player_down_0;
	void	*player_down_1;
	void	*player_down_2;
	void	*player_down_3;
	// void	*player_left[5];
	void	*player_left_0;
	void	*player_left_1;
	void	*player_left_2;
	void	*player_left_3;
	// void	*player_right[5];
	void	*player_right_0;
	void	*player_right_1;
	void	*player_right_2;
	void	*player_right_3;
	/*---*/
}	t_img;

typedef struct s_trap
{
	int		x;
	int		y;
	int		frame;
	struct	s_trap* next;
}	t_trap;

typedef struct s_enemy
{
	int		x;
	int		y;
	int		frame;
	int		direction;
	struct	s_enemy* next;
}	t_enemy;

typedef struct s_data
{
	/*mlx*/
	void	*mlx;
	void	*win;
	/*player*/
	int		*player_possition;
	int		collected_count;
	int		player_move_count;
	int		player_frame;
	int		direction;
	/*trap*/
	t_trap	*trap_list;
	/*enemy*/
	t_enemy	*enemy_list;
	/*map*/
	char	**map;
	char	**map_copy;
	char	**map_cave;
	int		map_width;
	int		map_height;
	/*img*/
	t_img	*img;
	int		time;
	/*map check*/
	int		player_nbr;
	int		collectible_nbr;
	int		exit_nbr;
	int		*exit_possition;
	int		cave;
	/*dev*/
	int		printed;
	int		reachable_end;
	int 	design_mode;
	/*---*/
}	t_data;

void	pg(char **map, int *start, int *end, t_data *data);
void	start_game(t_data *data);
int		check_access(t_data *data, int *start, int *end);
void	pg2(char **map, int *start, int *end, t_data *data);
void	map_setup(t_data *data);
void	set_map_from_file(char *path, t_data *data);
int		check_map_tiles(t_data *data, int i, int j);
void	free_all(t_data *data);
char	**split_lines(char *all_line, int len, char **tab, int j);
int		open_file(char *path);
char	**new_mapcpy(char **map, int height, int width);
void	mapcpy(char **dest, char **map);
void	set_wall_tile(char ***map, t_data *data);
int		check_line_char(char *line, int line_nbr, int last_line);
int		check_common_errors(t_data *data);
int		check_map_tiles_helper(t_data *data, int i, int j);
void	check_collectible_access(t_data *data);

#endif