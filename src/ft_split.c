/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:50:22 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/21 19:07:32 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"
#include "print_error.h"

int	splitcount(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] == sep)
		i++;
	if (str[i])
	{
		count++;
		i++;
	}
	while (str[i])
	{
		if (str[i] != sep && str[i - 1] == sep)
			count++;
		i++;
	}
	return (count);
}

int	substrlen(const char *s, char sep)
{
	int	sublen;

	sublen = 0;
	while (s[sublen] != sep && s[sublen] != '\0')
		sublen++;
	return (sublen);
}

void	*freestrs(char **tab, size_t id)
{
	unsigned int	i;

	i = 0;
	while (i < id)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

char	**ft_split(char const *str, char sep)
{
	int		i;
	int		sublen;
	int		tabsize;
	char	*substr;
	char	**strs;

	tabsize = splitcount(str, sep);
	strs = malloc(sizeof(char *) * (tabsize + 1));
	if (!strs)
		return (print_error(ERR_MEM_ALLOC), NULL);
	i = 0;
	while (i < tabsize)
	{
		while (*str == sep)
			str++;
		sublen = substrlen(str, sep);
		substr = ft_substr(str, 0, sublen);
		if (!substr)
			return (freestrs(strs, i));
		strs[i++] = substr;
		str += sublen;
	}
	strs[i] = NULL;
	return (strs);
}
