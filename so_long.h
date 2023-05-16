/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:59:33 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/10 15:07:29 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
// # include <mlx.h>
# include <stdlib.h>
# include "get_next_line.h"
# include <fcntl.h>

# include <string.h>

typedef struct s_img
{
	int		img_width;
	int		img_height;
	void	*playerUp;
	void	*playerDown;
	void	*playerLeft;
	void	*playerRight;
	void	*floor;
	void	*topfloor;
	void	*wall0;
	void	*wall1;
	void	*wall2;
	void	*wall3;
	void	*wallLeft;
	void	*walldown;
	void	*wallRight;
	void	*wallTop;
	void	*insideCorner0;
	void	*insideCorner1;
	void	*insideCorner2;
	void	*insideCorner3;
	void	*coll;
	void	*exit_tile;
}	t_img;

typedef struct s_data
{
	/*mlx*/
	void	*mlx;
	void	*win;
	/*player*/
	int     *player_possition;
	int	 	collected_count;
	int		player_move_count;
	int		player_frame;
	/*map*/
	char	**map;
	char	**map_copy;
	char	**map_cave;
	int     map_width;
	int     map_height;
	/*img*/
	t_img	*img; 
	/*map check*/
	int     player_nbr;
	int     collectible_nbr;
	int     exit_nbr;
	int     *exit_possition;
	int		cave;
	/*dev*/
	int		printed;
	int     reachable_end;
	/*---*/
}	t_data;

/*dev*/
typedef struct t_propagation_data
{
	int x;
	int y;
	struct t_propagation_data *parent;
}   t_propagation_data;
/*---*/

void pg(char **map, int *start, int *end, t_data *data);
void	start_game(t_data *data);
void print_map(char **map);
int check_access(t_data *data, int *start, int *end);
void pg2(char **map, int *start, int *end, t_data *data);
void map_setup(t_data *data);
void set_map_from_file(char *path, t_data *data);
int check_map_tiles(t_data *data);
void free_all(t_data *data);
char **split_lines(char *all_line, int len, char **tab, int j);
int open_file(char *path);
char **new_mapcpy(char **map, int height, int width);


#endif