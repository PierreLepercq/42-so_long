/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 17:39:45 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 16:36:52 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <X11/keysym.h>
#include "../so_long.h"
#include "print_utils.h"

int	get_tile_index(char tile)
{
	int	tile_id;

	tile_id = 0;
	while (MAP_TILES[tile_id])
	{
		if (MAP_TILES[tile_id] == tile)
			return (tile_id + 1);
		tile_id++;
	}
	return (0);
}

void	tile_render(t_game *g, char tile, int pos_x, int pos_y)
{
	int	x;
	int	y;
	int	tile_id;

	x = pos_x * TEX_SIZE;
	y = pos_y * TEX_SIZE;
	tile_id = get_tile_index(tile);
	mlx_put_image_to_window(g->mlx, g->mlx_win, g->txs[tile_id].img, x, y);
}

void	move(t_game *g, t_coord2d next)
{
	t_coord2d	play;
	t_coord2d	dest;

	play = g->player.pos;
	if (g->map.grid[play.y][play.x] == TILE_EXIT && g->win)
		game_exit(NULL);
	dest = coord2d(play.x + next.x, play.y + next.y);
	if (g->map.grid[dest.y][dest.x] == TILE_WALL)
		return ;
	if (g->map.grid[dest.y][dest.x] == TILE_COLLECTIBLE)
		g->player.nbr_collectibles++;
	if (g->map.grid[dest.y][dest.x] == TILE_EXIT
		&& g->player.nbr_collectibles != g->map.nbr_collectibles)
		return ;
	tile_render(g, TILE_GROUND, play.x, play.y);
	tile_render(g, TILE_PLAYER, dest.x, dest.y);
	g->player.pos = dest;
	g->player.moves++;
	if (g->map.grid[dest.y][dest.x] == TILE_EXIT)
	{
		g->win = 1;
		print_win(g->player.moves);
	}
	else
		print_moves(g->player.moves);
}

int	key_hook(int keysym, void *game)
{
	if (keysym == 'w' || keysym == KEY_UP)
		move(game, coord2d(0, -1));
	if (keysym == 'a' || keysym == KEY_LEFT)
		move(game, coord2d(-1, 0));
	if (keysym == 's' || keysym == KEY_DOWN)
		move(game, coord2d(0, 1));
	if (keysym == 'd' || keysym == KEY_RIGHT)
		move(game, coord2d(1, 0));
	if (keysym == K_ESC)
		game_exit(NULL);
	return (0);
}

void	mlx_window_init(t_game *game)
{
	int	win_h;
	int	win_w;

	win_h = game->map.height * TEX_SIZE;
	win_w = game->map.width * TEX_SIZE;
	game->mlx_win = mlx_new_window(game->mlx, win_w, win_h, WIN_TITLE);
	if (!game->mlx_win)
		game_exit(ERR_MLX_WIN_INIT_FAILED);
	mlx_key_hook(game->mlx_win, key_hook, game);
	mlx_hook(game->mlx_win, 17, 0L, (void *)game_exit, NULL);
}
