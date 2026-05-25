/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:57:42 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 21:39:01 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>			// NULL
#include <stdlib.h>			// malloc, free
#include <unistd.h> 		// read, close
#include "ft_string.h"		// ft_strjoin
#include "print_error.h"
#include "read_file.h"

static char	*str_extend(char **s1, char *s2)
{
	char	*s3;

	if (!s1 || !*s1 || !s2)
		return (NULL);
	s3 = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = s3;
	return (s3);
}

char	*read_file(int fd)
{
	int		nbr_bytes;
	char	*buffer;
	char	*file_content;

	file_content = malloc(1);
	if (!file_content)
		return (print_error(ERR_MEM_ALLOC), NULL);
	*file_content = '\0';
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (print_error(ERR_MEM_ALLOC), free(file_content), NULL);
	nbr_bytes = read(fd, buffer, BUFFER_SIZE);
	while (nbr_bytes > 0 && file_content)
	{
		buffer[nbr_bytes] = '\0';
		str_extend(&file_content, buffer);
		nbr_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (!file_content)
		return (print_error(ERR_MEM_ALLOC), NULL);
	if (nbr_bytes == -1)
		return (free(file_content), NULL);
	return (file_content);
}
