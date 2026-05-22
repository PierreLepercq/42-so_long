/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:36:04 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/22 01:22:38 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stddef.h>			// NULL
#include <stdlib.h>			// malloc, free
#include <stdbool.h>
#include "so_long.h"

t_game game;

int	game_init(char *map_file)
{
	map_init(&game.map);
	map_load(&game.map, map_file);
	player_init(&game.player);
	game.player.pos = game.map.start;
	//game.mlx = mlx_init();
	//if (!game.mlx)
	//	game_exit(ERR_MLX_INIT_FAILED);
	//assets_init(g);
	//g->mlx_win = NULL;
	return (0);
}

int	game_launch()
{
	//map_draw();
	return (0);
}

int	game_clear(void)
{
	return (0);
}

int	game_exit(char *err_msg)
{
	map_clean(&game.map);
	if (err_msg)
		print_error(err_msg);
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
