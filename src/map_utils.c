/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 18:52:48 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 18:14:02 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "ft_split.h"

int	char_count(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

int	get_dimensions(char *ascii, int *height, int *width)
{
	int	h;
	int	w;
	int	sublen;

	h = 0;
	w = 0;
	while (ascii[w] && ascii[w] != '\n')
		w++;
	while (*ascii)
	{
		h++;
		sublen = substrlen(ascii, '\n');
		if (sublen != w)
			return (1);
		if (ascii[sublen] == '\n')
			sublen++;
		ascii += sublen;
	}
	if (h < 3 || w < 3)
		return (1);
	*height = h;
	*width = w;
	return (0);
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
