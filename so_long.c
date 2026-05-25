/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:36:04 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 21:37:09 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "print_error.h"
#include "so_long.h"

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
	void	*player_img;

	map_draw(game);
	player_img = game->txs[get_tile_index(TILE_PLAYER)].img;
	tile_render(game, player_img, game->player.pos.x, game->player.pos.y);
	mlx_loop(game->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_error(ERR_FILE_NOT_PROVIDED);
		exit(EXIT_SUCCESS);
	}
	game_init(&game, argv[1]);
	game_launch(&game);
	game_exit(&game, NULL);
	return (0);
}
