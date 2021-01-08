/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:30:59 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static inline int	bytes_cmp(const void *b1, const void *b2, const size_t n)
{
	const unsigned char *restrict	s1 = (unsigned char *)b1;
	const unsigned char *restrict	s2 = (unsigned char *)b2;
	register size_t					i;

	i = 0;
	while (i < n)
	{
		if (*s1 ^ *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
		i++;
	}
	return (0);
}

/*
** @brief Compare memory areas.
** @details Compares the first @a n bytes of the memory areas @a b1 and @a b2.
** @param [in] b1 Memory area.
** @param [in] b2 Memory area.
** @param [in] n Size of memory to compare.
** @return An integer less than, equal to, or greater than zero if @a b1 is
** found, respectively, to be less than, to match, or be greater than @a b2.
** @ingroup mem
*/

int					ft_memcmp(const void *b1, const void *b2, size_t n)
{
	const size_t *restrict			b1_64 = b1;
	const size_t *restrict			b2_64 = b2;
	register size_t					xn;

	xn = n / sizeof(size_t);
	while (xn)
	{
		if (*b1_64 ^ *b2_64)
			return (bytes_cmp(b1_64, b2_64, sizeof(size_t)));
		b1_64++;
		b2_64++;
		xn--;
	}
	return (bytes_cmp(b1_64, b2_64, n % sizeof(size_t)));
}
