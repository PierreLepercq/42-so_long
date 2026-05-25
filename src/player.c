/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 01:11:41 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/22 17:39:42 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "so_long.h"

void    player_init(t_player *player)
{
    player->pos = coord2d(-1, -1);
    player->moves = 0;
    player->state = 0;
    player->nbr_collectibles = 0;
}
