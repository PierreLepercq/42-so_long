/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:36:04 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/24 17:52:39 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stddef.h>			// NULL
#include <stdlib.h>			// malloc, free
#include <stdbool.h>
#include "so_long.h"

t_game game;

int	game_exit(char *err_msg)
{
	if (game.mlx_win)
		mlx_destroy_window(game.mlx, game.mlx_win);
	textures_clear(&game);
	if (game.mlx)
	{
		mlx_destroy_display(game.mlx);
		free(game.mlx);
		game.mlx = NULL;
	}
	map_clear(&game.map);
	if (err_msg)
	{
		print_error(err_msg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	game_init(char *map_file)
{
	map_init(&game.map);
	if (map_load(&game.map, map_file) == FAIL)
		game_exit(NULL);
	player_init(&game.player);
	game.player.pos = game.map.start;
	game.mlx = mlx_init();
	if (!game.mlx)
		game_exit(ERR_MLX_INIT_FAILED);
	textures_init(game.txs);
	if (textures_load(&game) == FAIL)
		game_exit(ERR_TXS_NOT_LOADED);
	mlx_window_init(&game);
	return (0);
}

int	game_launch()
{
	map_draw(&game);
	tile_render(&game, TILE_PLAYER, game.player.pos.x, game.player.pos.y);
	mlx_loop(game.mlx);
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
