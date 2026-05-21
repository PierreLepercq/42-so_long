/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:40:04 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/14 20:44:02 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdbool.h>
# include "coord.h"

# define MAP_TILES			"0PE1C"
# define TILE_EMPTY			'0'
# define TILE_START			'P'
# define TILE_EXIT			'E'
# define TILE_WALL			'1'
# define TILE_COLLECTIBLE	'C'
# define TILE_VISITED		'V'

typedef struct s_map
{
	char		*ascii;
	char		**grid;
	int			height;
	int			width;
	int			nbr_collectibles;
	t_coord2d	start;
	t_coord2d	exit;
}				t_map;

//	MAP CHECKS
bool		is_suffix_valid(char *s, char *suffix);
bool		is_map_content_valid(char **grid);
bool		is_map_rectangular(char **grid, int *height, int *width);
bool		is_map_enclosed(char **grid);
bool		is_map_tile_unique(char **grid, char tile);

//	MAP FIND
char		**gridcpy(char **strs);
int			map_count(char **grid, char tile);
t_coord2d	map_find(char **grid, char tile);
bool		flood_fill(char **grid, t_coord2d pos, t_coord2d target);
bool		is_reachable(char **grid, t_coord2d start, t_coord2d target);

//	MAP LOAD
bool		is_map_grid_valid(char **grid);
t_map		*map_new(char *ascii);
void		map_free(t_map **map);
t_map		*load_map_file(char *file);

#endif