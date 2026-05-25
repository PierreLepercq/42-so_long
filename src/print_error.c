/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 21:23:09 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 21:35:56 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "print_error.h"

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
