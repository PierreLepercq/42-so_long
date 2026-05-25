/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:36:04 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 18:47:40 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "so_long.h"
#include "print_utils.h"

int	game_exit(t_game *game, char *err_msg)
{
	if (game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	textures_clear(game);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	map_clear(&game->map);
	if (err_msg)
	{
		print_error(err_msg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	game_init(t_game *game, char *map_file)
{
	game->win = 0;
	game->mlx = NULL;
	game->mlx_win = NULL;
	map_init(&game->map);
	textures_init(game->txs);
	player_init(&game->player);
	game->mlx = mlx_init();
	if (!game->mlx)
		game_exit(game, ERR_MLX_INIT_FAILED);
	if (map_load(&game->map, map_file) == FAIL)
		game_exit(game, NULL);
	game->player.pos = game->map.start;
	textures_load(game);
	mlx_window_init(game);
	return (0);
}

int	game_launch(t_game *game)
{
	map_draw(game);
	tile_render(game, TILE_PLAYER, game->player.pos.x, game->player.pos.y);
	mlx_loop(game->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (print_error("File not provided"), 1);
	game_init(&game, argv[1]);
	game_launch(&game);
	game_exit(&game, NULL);
	return (0);
}
