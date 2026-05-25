/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 15:21:27 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 20:55:48 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../so_long.h"

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
	tx_init(&txs[WIN]);
}

void	tx_load(t_game *g, t_texture *tx, char *tx_path)
{
	tx->img = mlx_xpm_file_to_image(g->mlx, tx_path, &tx->width, &tx->height);
	if (!tx->img)
		game_exit(g, ERR_TX_NOT_LOADED);
	if (tx->height != TEX_SIZE || tx->width != TEX_SIZE)
		game_exit(g, ERR_TX_SIZE_NOT_CORRECT);
}

void	textures_load(t_game *g)
{
	tx_load(g, &g->txs[NO_TEX], TEX_NO_TEX);
	tx_load(g, &g->txs[GROUND], TEX_GROUND);
	tx_load(g, &g->txs[WALL], TEX_WALL);
	tx_load(g, &g->txs[PLAYER], TEX_PLAYER);
	tx_load(g, &g->txs[EXIT], TEX_EXIT);
	tx_load(g, &g->txs[COLLECTIBLE], TEX_COLLECTIBLE);
	tx_load(g, &g->txs[WIN], TEX_WIN);
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
