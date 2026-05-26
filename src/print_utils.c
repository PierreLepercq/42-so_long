/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:38:35 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 21:59:20 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../so_long.h"

void	writenbr(int n, int fd)
{
	char	cn;

	if (n < -9 || n > 9)
		writenbr(n / 10, fd);
	if (n < 0)
		cn = '0' - (n % 10);
	else
		cn = '0' + (n % 10);
	write(fd, &cn, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		writenbr(n, fd);
	}
	else
		writenbr(n, fd);
}

void	print_moves(int nbr_moves)
{
	write(1, "Moves : ", 8);
	ft_putnbr_fd(nbr_moves, 1);
	write(1, "\n", 1);
}

void	print_win(t_game *g)
{
	write(1, "#######################################################\n\n", 57);
	write(1, "                * YOU WIN *  ᕙ (`▽ ´)ᕗ\n\n", 47);
	write(1, "  Total moves : ", 16);
	ft_putnbr_fd(g->player.moves, 1);
	write(1, "\n  Try again to see if you can do it in fewer moves!\n", 53);
	write(1, "#######################################################\n", 56);
}
