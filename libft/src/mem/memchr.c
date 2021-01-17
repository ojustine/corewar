/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:04:50 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include "mem.h"

static inline size_t	hasbyte(size_t word, unsigned char byte)
{
	static const size_t ones = (size_t)-1 / UCHAR_MAX;
	static const size_t highs = ones * (UCHAR_MAX / 2 + 1);
	const size_t		mask = word ^ (ones * byte);

	return ((mask - ones) & ~mask & highs);
}

/*
** @brief Locates the first occurrence of byte in memory area.
** @details Scans the first @a n bytes of the memory
** area pointed to by @a src for the character @a c. The first byte to match @a
** c (interpreted as an unsigned character) stops the operation.
** @param src Memory area;
** @param c Sought byte.
** @param n Size of memory to find.
** @return A pointer to the matching byte or NULL if the character does not
** occur in the given memory area.
** @ingroup mem
*/

void					*ft_memchr(const void *src, int c, size_t n)
{
	const t_byte *restrict	s8 = (const t_byte *)src;
	const size_t *restrict	s64;

	c = (t_byte)c;
	while (((size_t)s8 & (sizeof(size_t) - 1)) && n && *s8 != c)
	{
		s8++;
		n--;
	}
	if (n >= sizeof(size_t) && *s8 != c)
	{
		s64 = (const void *)s8;
		while (n >= sizeof(size_t) && !hasbyte(*s64, c))
		{
			s64++;
			n -= sizeof(size_t);
		}
		s8 = (const void *)s64;
	}
	while (n && *s8 != c)
	{
		n--;
		s8++;
	}
	return (n ? (void *)s8 : (void *)0);
}

/*
** @brief Locates the last occurrence of byte in memory area.
** @details Scans the first @a n bytes of the memory
** area pointed to by @a src for the character @a c. The last byte to match @a c
** (interpreted as an unsigned character) stops the operation.
** @param src Memory area;
** @param c Sought byte.
** @param n Size of memory to find.
** @return A pointer to the matching byte or NULL if the character does not
** occur in the given memory area.
** @ingroup mem
*/

void					*ft_memrchr(const void *src, int c, size_t n)
{
	const t_byte *restrict	s8 = (const t_byte *)src + n - 1;
	const size_t *restrict	s64;

	c = (unsigned char)c;
	while (((size_t)s8 & (sizeof(size_t) - 1)) && n && *s8 != c)
	{
		s8--;
		n--;
	}
	if (n >= sizeof(size_t) && *s8 != c)
	{
		s64 = (const void *)(s8 - sizeof(size_t));
		while (n >= sizeof(size_t) && !hasbyte(*s64, c))
		{
			--s64;
			n -= sizeof(size_t);
		}
		s8 = (const void *)(s64 + 1);
	}
	while (n && *s8 != c)
	{
		n--;
		s8--;
	}
	return (n ? (void *)s8 : (void *)0);
}
