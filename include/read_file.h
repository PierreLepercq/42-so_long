/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:59:24 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 15:44:32 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_FILE_H
# define READ_FILE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*read_file(int fd);

#endif