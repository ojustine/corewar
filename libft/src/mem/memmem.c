/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:45:46 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

#define ALPHABET_SIZE	(UCHAR_MAX + 1)

static inline size_t	hash2(const unsigned char *p)
{
	return (((size_t)p[0] - ((size_t)p[-1] << 3U)) % ALPHABET_SIZE);
}

static inline size_t	do_shift(unsigned char *shift_table, const size_t n,
						const unsigned char *restrict ne, size_t *offset)
{
	register size_t	i;
	size_t			shift;

	ft_memset(shift_table, 0, ALPHABET_SIZE);
	i = 1;
	while (i < n)
	{
		shift_table[hash2(ne + i)] = i;
		i++;
	}
	shift = n - shift_table[hash2(ne + n)];
	shift_table[hash2(ne + n)] = n;
	*offset = 0;
	return (shift);
}

static void				*search_256_bytes(const unsigned char *restrict hs,
						const unsigned char *hs_end, const unsigned char *ne,
						const size_t ne_len)
{
	unsigned char	shift_table[ALPHABET_SIZE];
	size_t			tmp;
	size_t			offset;
	const size_t	shift = do_shift(shift_table, ne_len - 1, ne, &offset);

	while (hs <= hs_end && (hs += ne_len - 1))
	{
		tmp = shift_table[hash2(hs)];
		while (tmp == 0 && hs <= hs_end)
		{
			hs += ne_len - 1;
			tmp = shift_table[hash2(hs)];
		}
		hs -= tmp;
		if (tmp < ne_len - 1)
			continue ;
		if (ne_len < 16 || ft_memcmp(hs + offset, ne + offset, 8) == 0)
		{
			if (ft_memcmp(hs, ne, ne_len - 1) == 0)
				return ((void *)hs);
			offset = (offset >= 8 ? offset : ne_len - 1) - 8;
		}
		hs += shift;
	}
	return (NULL);
}

static void				*search_raita(const void *haystack, size_t hs_len,
						const void *needle, size_t ne_len)
{
	const unsigned char *restrict	hs = (unsigned char *)haystack;
	const unsigned char *restrict	ne = (unsigned char *)needle;
	size_t							shift_table[UCHAR_MAX + 1];
	unsigned char					c;
	register size_t					i;

	i = 0;
	while (i < UCHAR_MAX + 1)
		shift_table[i++] = ne_len;
	i = 0;
	while (i < ne_len - 1)
	{
		shift_table[ne[i]] = ne_len - i - 1;
		i++;
	}
	i = 0;
	while (i <= hs_len - ne_len)
	{
		c = hs[i + ne_len - 1];
		if (ne[ne_len - 1] == c && ne[ne_len / 2] == hs[i + ne_len / 2]
			&& ne[0] == hs[i] && ft_memcmp(ne + 1, hs + i + 1, ne_len - 2) == 0)
			return ((void *)(&hs[i]));
		i += shift_table[c];
	}
	return (NULL);
}

/*
** @brief Locate a byte substring in a byte string.
** @details Finds the start of the first occurrence of the substring @a needle
** of length @a ne_len in the memory area @a haystack of length @a hs_len.
**@param haystack Memory area the big.
** @param hs_len Size of @a haystack.
** @param needle Memory area the little.
** @param ne_len Size of @a needle.
** @return Returns a pointer to the beginning of the substring,
** or NULL if the substring is not found.
** @ingroup mem
*/

void					*ft_memmem(const void *haystack, size_t hs_len,
						const void *needle, size_t ne_len)
{
	const unsigned char *restrict	hs = (const unsigned char *)haystack;
	const unsigned char *restrict	ne = (const unsigned char *)needle;
	const unsigned char				*end = hs + hs_len - ne_len;
	register uint32_t				nw;
	register uint32_t				hw;

	if (ne_len == 0)
		return ((void *)haystack);
	if (ne_len == 1)
		return (ft_memchr(hs, *ne, hs_len));
	if (hs_len < ne_len)
		return (NULL);
	if (ne_len == 2)
	{
		end = hs + hs_len - 2;
		nw = ne[0] << 16U | ne[1];
		hw = hs[0] << 16U | hs[1];
		hs++;
		while (hs <= end && hw != nw)
			hw = hw << 16 | *++hs;
		return (hw == nw ? (void *)hs - 1 : NULL);
	}
	if (ne_len <= ALPHABET_SIZE)
		return (search_256_bytes(hs, end, ne, ne_len));
	return (search_raita(haystack, hs_len, needle, ne_len));
}
