/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 17:39:45 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/26 03:18:12 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <X11/keysym.h>
#include "../so_long.h"

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

void	tile_render(t_game *g, void	*img, int pos_x, int pos_y)
{
	int	x;
	int	y;

	x = pos_x * TEX_SIZE;
	y = pos_y * TEX_SIZE;
	mlx_put_image_to_window(g->mlx, g->mlx_win, img, x, y);
}

void	move(t_game *g, t_coord2d next)
{
	t_coord2d	prev;
	t_coord2d	dest;
	int			tile_id;

	prev = g->player.pos;
	dest = coord2d(prev.x + next.x, prev.y + next.y);
	if (g->map.grid[prev.y][prev.x] == TILE_EXIT && g->win)
		game_exit(g, NULL);
	if (player_move(g, dest) == FAIL)
		return ;
	if (g->map.grid[dest.y][dest.x] == TILE_EXIT && g->win)
		tile_render(g, g->txs[EXIT_WIN].img, dest.x, dest.y);
	else
		tile_render(g, g->txs[PLAYER].img, dest.x, dest.y);
	tile_id = get_tile_index(g->map.grid[prev.y][prev.x]);
	tile_render(g, g->txs[tile_id].img, prev.x, prev.y);
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
		game_exit(game, NULL);
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
		game_exit(game, ERR_MLX_WIN_INIT_FAILED);
	mlx_key_hook(game->mlx_win, key_hook, game);
	mlx_hook(game->mlx_win, 17, 0L, (void *)game_exit, game);
}
