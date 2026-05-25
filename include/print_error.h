/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 21:33:57 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 21:36:27 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_ERROR_H
# define PRINT_ERROR_H

# define ERR_MEM_ALLOC				"Memory allocation failed"
# define ERR_OPEN_FILE 				"Unable to open file"

void	print_error(const char *err_msg);

#endif