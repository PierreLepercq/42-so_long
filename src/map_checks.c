/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 18:30:19 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 21:53:12 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../so_long.h"
#include "ft_split.h"
#include "ft_string.h"
#include "print_error.h"

bool	is_suffix_valid(char *s, char *suffix)
{
	int	i;
	int	len;
	int	suf_len;

	len = ft_strlen(s);
	suf_len = ft_strlen(suffix);
	if (len <= suf_len)
		return (false);
	i = 0;
	while (i < suf_len)
	{
		if (s[len - suf_len + i] != suffix[i])
			return (false);
		i++;
	}
	return (true);
}

bool	is_map_content_valid(char *ascii)
{
	while (*ascii)
	{
		if (*ascii != '\n' && !ft_strrchr(MAP_TILES, *ascii))
			return (false);
		ascii++;
	}
	return (true);
}

bool	is_map_enclosed(char *ascii, int height, int width)
{
	int	i;
	int	mod_nl;

	i = 0;
	mod_nl = width + 1;
	while (ascii[i])
	{
		if (i % mod_nl == 0 && ascii[i] != TILE_WALL)
			return (false);
		if (i % mod_nl == width - 1 && ascii[i] != TILE_WALL)
			return (false);
		if (i / mod_nl == 0 || i / mod_nl == height - 1)
		{
			if (i % mod_nl <= width - 1 && ascii[i] != TILE_WALL)
				return (false);
		}
		i++;
	}
	return (true);
}

bool	is_map_playable(char *ascii, int height)
{
	int			y;
	int			x;
	t_coord2d	start;
	char		**grid;

	grid = ft_split(ascii, '\n');
	if (!grid)
		return (print_error(ERR_MEM_ALLOC), false);
	start = map_find(grid, TILE_PLAYER);
	if (!is_reachable(grid, start, map_find(grid, TILE_EXIT)))
		return (freestrs(grid, height), false);
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == TILE_COLLECTIBLE
				&& !is_reachable(grid, coord2d(x, y), start))
				return (freestrs(grid, height), false);
			x++;
		}
		y++;
	}
	return (freestrs(grid, height), true);
}

bool	is_map_valid(char *ascii)
{
	int	h;
	int	w;
	int	nbr_c;

	if (!is_map_content_valid(ascii))
		return (print_error(ERR_MAP_BAD_CONTENT), false);
	if (char_count(ascii, TILE_PLAYER) != 1)
		return (print_error(ERR_PLAYER_NOT_UNIQUE), false);
	if (char_count(ascii, TILE_EXIT) != 1)
		return (print_error(ERR_EXIT_NOT_UNIQUE), false);
	nbr_c = char_count(ascii, TILE_COLLECTIBLE);
	if (nbr_c == 0)
		return (print_error(ERR_NO_COLLECTIBLES), false);
	if (get_dimensions(ascii, &h, &w))
		return (print_error(ERR_MAP_NOT_RECT), false);
	if (!is_map_enclosed(ascii, h, w))
		return (print_error(ERR_MAP_NOT_ENCLOSED), false);
	if (h * TEX_SIZE >= WIN_MAX_HEIGHT || w * TEX_SIZE >= WIN_MAX_WIDTH)
		return (print_error(ERR_MAP_TOO_BIG), false);
	if (!is_map_playable(ascii, h))
		return (print_error(ERR_MAP_IS_NOT_PLAYABLE), false);
	return (true);
}
