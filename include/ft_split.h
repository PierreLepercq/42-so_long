/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 13:58:39 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 14:29:42 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPLIT_H
# define FT_SPLIT_H

# include <stddef.h>

int		splitcount(const char *str, char sep);
int		substrlen(const char *s, char sep);
void	*freestrs(char **tab, size_t id);
char	**ft_split(char const *str, char sep);

#endif