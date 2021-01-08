/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:59:49 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <limits.h>

#define ONES	((size_t)-1 / UCHAR_MAX)
#define HIGHS	(ONES * (UCHAR_MAX / 2 + 1))

static inline int	haszero(size_t word)
{
	return (((word - ONES) & ~word & HIGHS) != 0);
}

size_t				ft_strlen(const char *s)
{
	const char *restrict	s8 = s;
	const size_t *restrict	s64;

	while (((size_t)s8 & sizeof(size_t) - 1) && *s8)
		s8++;
	if (*s8)
	{
		s64 = (const size_t *)s8;
		while (!haszero(*s64))
			s64++;
		s8 = (const char *)s64;
	}
	while (*s8)
		s8++;
	return (s8 - s);
}
