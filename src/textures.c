/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 15:21:27 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 14:01:58 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stddef.h>
#include "so_long.h"

void	tx_init(t_texture *tx)
{
	tx->img = NULL;
	tx->height = 0;
	tx->width = 0;
}

void	textures_init(t_texture *txs)
{
	tx_init(&txs[NO_TEX]);
	tx_init(&txs[GROUND]);
	tx_init(&txs[WALL]);
	tx_init(&txs[PLAYER]);
	tx_init(&txs[EXIT]);
	tx_init(&txs[COLLECTIBLE]);
}

void	tx_load(void *mlx, t_texture *tx, char *tx_path)
{
	tx->img = mlx_xpm_file_to_image(mlx, tx_path, &tx->width, &tx->height);
	if (tx->height != TEX_SIZE || tx->width != TEX_SIZE)
		game_exit(ERR_TXS_SIZE_NOT_CORRECT);
}

int	textures_load(t_game *g)
{
	int	i;

	tx_load(g->mlx, &g->txs[NO_TEX], "./textures/no_texture.xpm");
	tx_load(g->mlx, &g->txs[GROUND], "./textures/ground.xpm");
	tx_load(g->mlx, &g->txs[WALL], "./textures/wall.xpm");
	tx_load(g->mlx, &g->txs[PLAYER], "./textures/player.xpm");
	tx_load(g->mlx, &g->txs[EXIT], "./textures/exit.xpm");
	tx_load(g->mlx, &g->txs[COLLECTIBLE], "./textures/collectible.xpm");
	i = 0;
	while (i < TEX_NBR)
	{
		if (!g->txs[i].img)
			return (1);
		i++;
	}
	return (0);
}

void	textures_clear(t_game *game)
{
		int	i;

	if (!game->mlx)
		return ;
	i = 0;
	while (i < TEX_NBR)
	{
		if (game->txs[i].img)
		{
			mlx_destroy_image(game->mlx, game->txs[i].img);
			game->txs[i].img = NULL;
		}
		i++;
	}
}
