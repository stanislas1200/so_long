/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:59:33 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/20 16:38:24 by sgodin           ###   ########.fr       */
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
	void	*exit_tile;
	void	*unknown_tile;
	/*outside*/
	void	*outside_tiles[17];
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
	void	*collectible[3];
	void	*collectible0;
	void	*collectible1;
	/*cave*/
	void	*inside_tiles[17];
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
	void	*cave_collectible[3];
	void	*cave_collectible0;
	void	*cave_collectible1;
	/*---*/
	/*player*/
	void	**player[5][5];
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
	/*---*/
}	t_data;

void	pg(char **map, int *start, int *end, t_data *data);
void	start_game(t_data *data);
void	print_map(char **map);
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