/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:32:50 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/13 14:57:49 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COORD_H
# define COORD_H

typedef struct s_coord2d
{
	int		x;
	int		y;
}			t_coord2d;

t_coord2d	coord2d(int x, int y);

#endif