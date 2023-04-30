/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:59:33 by sgodin            #+#    #+#             */
/*   Updated: 2023/04/29 17:16:53 by sgodin           ###   ########.fr       */
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

typedef struct s_data
{
	/*mlx*/
	void	*mlx;
	void	*win;
	/*player*/
	int     *player_possition;
	int	 	collected_count;
	int		player_move_count;
	/*map*/
	char	**map;
	char	**map_copy;
	int     map_width;
	int     map_height;
	/*map check*/
	int     player_nbr;
	int     collectible_nbr;
	int     exit_nbr;
	int     reachable_end;
	int     *exit_possition;
	/*img*/
	void	*player_image;
	void	*floor;
	void	*wall;
	void	*coll;
	void	*exit_tile;
	/*dev*/
	int		printed;
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

void propagate(char **map, int *start, int *end, t_data *data, t_propagation_data *parent);
void	start_game(t_data *data);


#endif