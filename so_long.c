/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:36:04 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 16:11:18 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "so_long.h"
#include "print_utils.h"

t_game	g_game;

int	game_exit(char *err_msg)
{
	if (g_game.mlx_win)
		mlx_destroy_window(g_game.mlx, g_game.mlx_win);
	textures_clear(&g_game);
	if (g_game.mlx)
	{
		mlx_destroy_display(g_game.mlx);
		free(g_game.mlx);
		g_game.mlx = NULL;
	}
	map_clear(&g_game.map);
	if (err_msg)
	{
		print_error(err_msg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	game_init(char *map_file)
{
	g_game.win = 0;
	map_init(&g_game.map);
	if (map_load(&g_game.map, map_file) == FAIL)
		game_exit(NULL);
	player_init(&g_game.player);
	g_game.player.pos = g_game.map.start;
	g_game.mlx = mlx_init();
	if (!g_game.mlx)
		game_exit(ERR_MLX_INIT_FAILED);
	textures_init(g_game.txs);
	if (textures_load(&g_game) == FAIL)
		game_exit(ERR_TXS_NOT_LOADED);
	mlx_window_init(&g_game);
	return (0);
}

int	game_launch(void)
{
	map_draw(&g_game);
	tile_render(&g_game, TILE_PLAYER, g_game.player.pos.x, g_game.player.pos.y);
	mlx_loop(g_game.mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (print_error("File not provided"), 1);
	game_init(argv[1]);
	game_launch();
	game_exit(NULL);
	return (0);
}
