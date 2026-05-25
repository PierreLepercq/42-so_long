/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:42:26 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 16:27:40 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_UTILS_H
# define PRINT_UTILS_H

# define ERR_MEM_ALLOC				"Memory allocation failed"
# define ERR_OPEN_FILE 				"Unable to open file"

void	writenbr(int n, int fd);
void	ft_putnbr_fd(int n, int fd);
void	print_moves(int nbr_moves);
void	print_win(int nbr_moves);
void	print_error(const char *err_msg);

#endif