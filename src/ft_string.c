/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:17:19 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 15:52:56 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "ft_string.h"

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strrchr(const char *s, int c)
{
	ssize_t	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	while (i >= 0)
	{
		if ((char)c == s[i])
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dest;

	len = ft_strlen(s);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	len = 0;
	while (s[len])
	{
		dest[len] = s[len];
		len++;
	}
	dest[len] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	int		sublen;
	char	*substr;

	if (ft_strlen(s) < start)
		sublen = 0;
	else
		sublen = ft_strlen(s) - start;
	if (len < (size_t)sublen)
		sublen = len;
	substr = malloc(sizeof(char) * (sublen + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < sublen)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	i = 0;
	len1 = ft_strlen(s1);
	len2 = len1 + ft_strlen(s2) + 1;
	while (i < len2)
	{
		if (i < len1)
			s3[i] = s1[i];
		else
			s3[i] = s2[i - len1];
		i++;
	}
	return (s3);
}
