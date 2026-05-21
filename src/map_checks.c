/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 17:55:44 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/14 14:23:16 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "map.h"
#include "ft_string.h"
#include "ft_split.h"
#include "print_error.h"

#include <stdio.h>

bool	is_suffix_valid(char *s, char *suffix)
{
	int	len;
	int	suf_len;

	len = ft_strlen(s);
	suf_len = ft_strlen(suffix);
	if (len == suf_len)
		return (false);
	if (ft_strncmp(s + (len - suf_len), suffix, suf_len))
		return (false);
	return (true);
}

bool	is_map_rectangular(t_map, int *height, int *width)
{
	int		i;
	size_t	len;
	bool	is_rect;

	i = 0;
	is_rect = true;
	len = ft_strlen(grid[i++]);
	while (grid[i])
	{
		if (ft_strlen(grid[i]) != len)
			is_rect = false;
		i++;
	}
	if (height)
		*height = i;
	if (width)
	{
		*width = -1;
		if (is_rect)
			*width = len;
	}
	return (is_rect);
}

bool	is_map_content_valid(char **grid)
{
	int		i;
	int		j;

	i = 0;
	while (grid[i])
	{
		j = ft_strlen(grid[i]);
		while (j >= 0)
		{
			if (!ft_strrchr(MAP_TILES, grid[i][j]))
				return (false);
			j--;
		}
		i++;
	}
	return (true);
}

bool	is_map_enclosed(char **grid)
{
	int	i;
	int	j;
	int	height;
	int	width;

	height = 0;
	while (grid[height])
		height++;
	height--;
	width = ft_strlen(grid[0]) - 1;
	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if ((i == 0 || i == height) && grid[i][j] != '1')
				return (false);
			if ((j == 0 || j == width) && grid[i][j] != '1')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	is_map_tile_unique(char **grid, char tile)
{
	if (map_count(grid, tile) == 1)
		return (true);
	return (false);
}
