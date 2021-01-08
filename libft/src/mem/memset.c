/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:30:59 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <limits.h>

#define ONES	((size_t)-1 / UCHAR_MAX)

static inline void	set_64(size_t *restrict b64, const size_t c64)
{
	b64[0] = c64;
	b64[1] = c64;
	b64[2] = c64;
	b64[3] = c64;
	b64[4] = c64;
	b64[5] = c64;
	b64[6] = c64;
	b64[7] = c64;
}

/*
** @brief Fill memory with a constant byte.
** @details Fills the first @a n bytes of the memory area pointed to by @a b
** with the constant byte @a c.
** @param [in] b Memory area.
** @param [in] n Size of memory to fill.
** @return Start of the memory @b.
** @ingroup mem
*/

void				*ft_memset(void *b, int c, size_t n)
{
	register size_t *restrict			b64;
	register unsigned char *restrict	b8;
	register size_t						xn;
	register const size_t				c64 = ONES * (unsigned char)c;

	b64 = (size_t *)b;
	xn = n / (sizeof(size_t) * 8);
	while (xn > 0)
	{
		set_64(b64, c64);
		b64 += 8;
		xn--;
	}
	n %= sizeof(size_t) * 8;
	xn = n / sizeof(size_t);
	while (xn > 0)
	{
		*b64++ = c64;
		xn--;
	}
	b8 = (unsigned char *)b64;
	n %= sizeof(size_t);
	while (n-- > 0)
		*b8++ = c;
	return (b);
}

/*
** @brief Zero a byte sequence.
** @details Erases the data in the \a n bytes of the memory starting at the
** location pointed to by \a b, by writing zeros (bytes containing '\0') to
** that area.
** @param [in] b Start of the memory area.
** @param [in] n Number of bytes.
** @return Start of the clean memory area.
** @ingroup mem
*/

void				*ft_bzero(void *b, size_t n)
{
	return (ft_memset(b, '\0', n));
}
