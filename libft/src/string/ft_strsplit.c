/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 14:42:28 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:27:15 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "mem.h"
#include "str.h"

static size_t	word_len(const char *s, char c)
{
	const char	*tmp = s;

	while (*tmp && *tmp != c)
		tmp++;
	return (tmp - s);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**split;
	size_t	w_len;
	size_t	i;

	if (!s || !(split = malloc(sizeof(char*) * (ft_words_count(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			w_len = word_len(s, c);
			split[i] = (char *)malloc((w_len + 1) * sizeof(char));
			if (!split[i])
				return (ft_free_split(split));
			ft_memcpy(split[i], s, w_len);
			split[i][w_len] = '\0';
			s += (w_len - 1);
			i++;
		}
		s++;
	}
	split[i] = NULL;
	return (split);
}
