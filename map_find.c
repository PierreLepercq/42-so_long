/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:13:22 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/21 20:14:48 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "so_long.h"
#include "ft_split.h"
#include "ft_string.h"

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
