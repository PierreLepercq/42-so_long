/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:38:35 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 14:54:44 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "print_utils.h"

void	print_error(const char *err_msg)
{
	int	len;

	len = 0;
	while (err_msg[len])
		len++;
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, err_msg, len);
	write(STDERR_FILENO, "\n", 1);
}
