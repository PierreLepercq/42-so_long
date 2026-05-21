/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:24:59 by plepercq          #+#    #+#             */
/*   Updated: 2026/01/09 23:46:25 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*str_extend(char **s1, char *s2)
{
	char	*s3;

	if (!*s1 || !s2)
		return (NULL);
	s3 = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = s3;
	return (s3);
}

char	*split_and_stash(char **stash)
{
	int		i;
	char	*tmp;
	char	*line;

	if (!*stash)
		return (NULL);
	i = 0;
	while ((*stash)[i] != '\n' && (*stash)[i] != '\0')
		i++;
	i++;
	line = ft_substr(*stash, 0, i);
	if (!line)
		return (free(*stash), *stash = NULL, NULL);
	tmp = ft_substr(*stash, i, ft_strlen(*stash));
	free(*stash);
	if (!tmp)
		return (free(line), *stash = NULL, NULL);
	if (tmp[0] == '\0')
	{
		free(tmp);
		tmp = NULL;
	}
	*stash = tmp;
	return (line);
}

char	*read_and_stash(int fd, char *stash)
{
	int		nbr_bytes;
	char	*buffer;

	if (!stash)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	nbr_bytes = read(fd, buffer, BUFFER_SIZE);
	while (nbr_bytes > 0 && stash)
	{
		buffer[nbr_bytes] = '\0';
		str_extend(&stash, buffer);
		if (ft_strrchr(buffer, '\n'))
			break ;
		nbr_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (!stash)
		return (NULL);
	if (nbr_bytes == -1 || (nbr_bytes == 0 && stash[0] == '\0'))
		return (free(stash), NULL);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
	{
		stash = malloc(sizeof(char));
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	if (!ft_strrchr(stash, '\n'))
		stash = read_and_stash(fd, stash);
	return (split_and_stash(&stash));
}
