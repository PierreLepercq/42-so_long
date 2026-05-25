/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord2d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 14:33:20 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 14:34:34 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COORD2D_H
# define COORD2D_H

typedef struct s_coord2d
{
	int			x;
	int			y;
}				t_coord2d;

t_coord2d	coord2d(int x, int y);

#endif