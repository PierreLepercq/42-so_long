/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 18:12:32 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 21:38:49 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../so_long.h"
#include "ft_split.h"
#include "read_file.h"
#include "print_error.h"

void	map_init(t_map *map)
{
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
	map->nbr_collectibles = 0;
	map->start = coord2d(-1, -1);
	map->exit = coord2d(-1, -1);
}

int	map_build(t_map *map, char *ascii)
{
	if (!is_map_valid(ascii))
		return (FAIL);
	map->grid = ft_split(ascii, '\n');
	if (!map->grid)
		return (FAIL);
	get_dimensions(ascii, &map->height, &map->width);
	map->nbr_collectibles = char_count(ascii, TILE_COLLECTIBLE);
	map->start = map_find(map->grid, TILE_PLAYER);
	map->exit = map_find(map->grid, TILE_EXIT);
	map->grid[map->start.y][map->start.x] = TILE_GROUND;
	return (PASS);
}

int	map_load(t_map *map, char *map_file)
{
	int		fd;
	int		build;
	char	*ascii;

	if (!is_suffix_valid(map_file, ".ber"))
		return (print_error(ERR_MAP_FILE_EXT), FAIL);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_OPEN_FILE), FAIL);
	ascii = read_file(fd);
	close(fd);
	if (!ascii)
		return (FAIL);
	build = map_build(map, ascii);
	free(ascii);
	return (build);
}

void	map_clear(t_map *map)
{
	freestrs(map->grid, map->height);
	map_init(map);
}

void	map_draw(t_game *g)
{
	int	y;
	int	x;
	int	tile_id;

	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			tile_id = get_tile_index(g->map.grid[y][x]);
			tile_render(g, g->txs[tile_id].img, x, y);
			x++;
		}
		y++;
	}
}
