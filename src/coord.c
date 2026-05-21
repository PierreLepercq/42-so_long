/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:31:30 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/13 14:59:14 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "coord.h"

t_coord2d	coord2d(int x, int y)
{
	t_coord2d	coord;

	coord.x = x;
	coord.y = y;
	return (coord);
}
