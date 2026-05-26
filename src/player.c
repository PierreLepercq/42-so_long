/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 01:11:41 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/26 03:17:41 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	player_init(t_player *player)
{
	player->pos = coord2d(-1, -1);
	player->moves = 0;
	player->state = 0;
	player->nbr_collectibles = 0;
}

int	player_move(t_game *g, t_coord2d dest)
{
	if (g->map.grid[dest.y][dest.x] == TILE_WALL)
		return (FAIL);
	if (g->map.grid[dest.y][dest.x] == TILE_EXIT
		&& g->player.nbr_collectibles != g->map.nbr_collectibles)
		return (FAIL);
	g->player.pos = dest;
	g->player.moves++;
	if (g->map.grid[dest.y][dest.x] == TILE_COLLECTIBLE)
	{
		g->map.grid[dest.y][dest.x] = TILE_GROUND;
		g->player.nbr_collectibles++;
		if (g->player.nbr_collectibles == g->map.nbr_collectibles)
			tile_render(g, g->txs[EXIT_OPEN].img, g->map.exit.x, g->map.exit.y);
	}
	if (g->map.grid[dest.y][dest.x] == TILE_EXIT
		&& g->player.nbr_collectibles == g->map.nbr_collectibles)
	{
		g->win = 1;
		print_win(g);
	}
	else
		print_moves(g->player.moves);
	return (PASS);
}
