/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:59:33 by sgodin            #+#    #+#             */
/*   Updated: 2023/04/26 15:24:50 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
// # include <mlx.h>
# include <stdlib.h>
# include "get_next_line.h"
# include <fcntl.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	**map;
    int     map_width;
    int     map_height;
    int     collectible_nbr;
    int     exit_nbr;
    int     player_nbr;
    int     *player_possition;
    int     *exit_possition;
    int     reachable_end;

}	t_data;

typedef struct Node {
    int x;
    int y;
    int walkable;
    int close;

    int g;
    int h;
    int f;

    struct Node* parent;
} Node;

typedef struct t_propagation_data
{
    int x;
    int y;
    struct t_propagation_data *parent;
}   t_propagation_data;


int *astar(char** map, int* start, int* end, int width, int height);
void propagate(char **map, int *start, int *end, t_data *data, t_propagation_data *parent);


#endif