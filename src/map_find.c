/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:13:22 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/14 20:44:02 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "map.h"
#include "ft_split.h"
#include "ft_string.h"
#include "print_error.h"

#include <stdio.h>

// TODO
//qu moins 1 collectible, 1 sortie, i plqyer
//pqs plus de 1 non plus pour sortie et player
//collectibles et sortie accessible

char	**gridcpy(char **strs)
{
	int		i;
	int		size;
	char	*str;
	char	**strs_cpy;

	size = 0;
	while (strs[size])
		size++;
	strs_cpy = malloc(sizeof(char *) * (size + 1));
	if (!strs_cpy)
		return (print_error(ERR_MEM_ALLOC), NULL);
	i = 0;
	while (i < size)
	{
		str = ft_strdup(strs[i]);
		if (!str)
		{
			freestrs(strs_cpy, i);
			return (print_error(ERR_MEM_ALLOC), NULL);
		}
		strs_cpy[i++] = str;
	}
	strs_cpy[i] = NULL;
	return (strs_cpy);
}

int	map_count(char **grid, char tile)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == tile)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

t_coord2d	map_find(char **grid, char tile)
{
	int	x;
	int	y;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == tile)
				return (coord2d(x, y));
			x++;
		}
		y++;
	}
	return (coord2d(-1, -1));
}

bool	flood_fill(char **grid, t_coord2d pos, t_coord2d target)
{
	if (grid[pos.y][pos.x] == TILE_WALL || grid[pos.y][pos.x] == TILE_VISITED)
		return (false);
	if (pos.x == target.x && pos.y == target.y)
		return (true);
	grid[pos.y][pos.x] = TILE_VISITED;
	if (flood_fill(grid, coord2d(pos.x, pos.y + 1), target)
		|| flood_fill(grid, coord2d(pos.x + 1, pos.y), target)
		|| flood_fill(grid, coord2d(pos.x, pos.y - 1), target)
		|| flood_fill(grid, coord2d(pos.x - 1, pos.y), target))
		return (true);
	return (false);
}

bool	is_reachable(char **grid, t_coord2d start, t_coord2d target)
{
	int		i;
	char	**grid_cpy;
	bool	reachable;

	i = 0;
	grid_cpy = gridcpy(grid);
	while (grid_cpy[i])
		i++;
	reachable = flood_fill(grid_cpy, start, target);
	freestrs(grid_cpy, i);
	return (reachable);
}
