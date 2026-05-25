/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 01:11:41 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 14:46:16 by plepercq         ###   ########.fr       */
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
