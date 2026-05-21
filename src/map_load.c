/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:26:02 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/14 14:25:07 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>			// NULL
#include <stdlib.h>			// malloc, free
#include <unistd.h>			// close
#include <fcntl.h>  		// open
#include "print_error.h"
#include "ft_string.h"
#include "ft_split.h"
#include "read_file.h"
#include "map.h"

#include <stdio.h>

bool	is_map_grid_valid(t_map *map)
{
	if (!is_map_rectangular(map, NULL, NULL))
		return (print_error(ERR_MAP_IS_NOT_RECT), false);
	if (!is_map_content_valid(map))
		return (print_error(ERR_MAP_BAD_CONTENT), false);
	if (!is_map_enclosed(map))
		return (print_error(ERR_MAP_NOT_ENCLOSED), false);
	if (!is_map_tile_unique(map, 'P') || !is_map_tile_unique(map, 'E'))
		return (print_error(ERR_MAP_TILE_NOT_UNIQUE), false);

	return (true);
}

bool	is_game_map_finishable(t_map *map)
{
	int			i;
	int			j;
	t_coord2d	start;
	t_coord2d	exit;

	start = map_find(map->grid, TILE_START);
	if (!is_reachable(grid, start, map_find(grid, TILE_EXIT)))
		return (print_error(ERR_MAP_ELEM_NOT_REACHABLE), false);
	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] != TILE_COLLECTIBLE)
				continue ;
			if (!is_reachable(grid, coord2d(j, i), start))
				return (print_error(ERR_MAP_ELEM_NOT_REACHABLE), false);
		}
	}
	return (true);
}

int	map_init(t_map *map, char *ascii)
{
	map->ascii = ft_strdup(ascii);
	














	grid = ft_split(ascii, '\n');
	if (!grid)
		return (print_error(ERR_MEM_ALLOC), map_free(map), NULL);
	if (!is_map_grid_valid(map) || !is_game_map_finishable(map))
	{
		freestrs(grid, height);
		return ;
	}
	map = malloc(sizeof(t_map));
	if (!map)
	{
		freestrs(grid, height);
		return (print_error(ERR_MEM_ALLOC), NULL);
	}
	map->grid = grid;
	map->height = height;
	map->width = ft_strlen(grid[0]);
	return (map);
}

void	map_free(t_map **map)
{
	int	height;

	if (!map || !(*map))
		return ;
	free((*map)->map_ascii);
	freestrs((*map)->grid, (*map)->height);
	free(map);
}

t_map	*load_map_file(char *file)
{
	int		fd;
	char	*ascii;
	t_map	*map;

	if (!is_suffix_valid(file, ".ber"))
		return (print_error(ERR_MAP_FILE_EXT), NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_MAP_OPEN_FILE), NULL);
	ascii = read_file(fd);
	close(fd);
	if (!ascii)
		return (print_error(ERR_MEM_ALLOC), NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (print_error(ERR_MEM_ALLOC), NULL);
	map_init(map, ascii);
	free(ascii);
	return (map);
}
