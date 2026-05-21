/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:38:35 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/05 15:07:41 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "print_error.h"

void	print_error(const char *error)
{
	int	len;

	len = 0;
	while (error[len])
		len++;
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, error, len);
	write(STDERR_FILENO, "\n", 1);
}
