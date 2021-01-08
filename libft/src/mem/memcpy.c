/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 00:05:49 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 20:37:25 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "mem.h"

/*
** @brief Copies memory.
** @details Copies @a n bytes from memory area @a src to memory area @a dst.
** @note The memory areas should not overlap.
** Use ft_memmove() if the memory areas do overlap.
** @param [in] dst Memory area - destination.
** @param [in] src Memory area - source.
** @param [in] n Size of memory to copy.
** @return Start of the destination memory.
** @see ft_memmove()
** @ingroup mem
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *restrict			d8;
	const unsigned char *restrict	s8 = src;
	size_t *restrict				d64;
	const size_t *restrict			s64 = src;
	register size_t					i;

	d8 = (unsigned char *)dst;
	d64 = (size_t *)dst;
	i = 0;
	while (i < (n / sizeof(size_t)))
	{
		*d64++ = *s64++;
		i++;
	}
	d8 += i * sizeof(size_t);
	s8 += i * sizeof(size_t);
	i = n % sizeof(size_t);
	while (i--)
		*d8++ = *s8++;
	return (dst);
}

/*
** @brief Copies the memory to the character.
** @details Copies no more than @a n bytes from memory area @a src to memory are
** @a dst, stopping when the character @a c is found.
** @note The memory areas should not overlap.
** @param [in] dst Memory area - destination.
** @param [in] src Memory area - source.
** @param [in] c Border byte.
** @param [in] n Size of memory to copy.
** @return Start of the destination memory.
** @ingroup mem
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const void *p = ft_memchr(src, c, n);

	if (p != NULL)
		return (ft_memcpy(dst, src, p - src + 1));
	return (ft_memcpy(dst, src, n));
}

/*
** @brief Copies memory.
** @details The mempcpy() function is nearly identical to the memcpy(3) function
** Copies @a n bytes from memory area @a src to memory area @a dst.
** But instead of returning the value of dest it returns a pointer to the byte
** following the last written byte.
** This function is useful in situations where a number of objects shall
** be copied to consecutive memory positions.
** @note The memory areas should not overlap.
** Use ft_memmove() if the memory areas do overlap.
** @param [in] dst Memory area - destination.
** @param [in] src Memory area - source.
** @param [in] n Size of memory to copy.
** @return A pointer to the byte following the last written byte.
** @see ft_memmove()
** @ingroup mem
*/

void	*ft_mempcpy(void *dst, const void *src, size_t n)
{
	return (ft_memcpy(dst, src, n) + n);
}

/*
** @brief Copies memory.
** @details Copies @a n bytes from memory area @a src to memory area @a dst.
** The memory areas may overlap.
** @param [in] dst Memory area - destination.
** @param [in] src Memory area - source.
** @param [in] n Size of memory to copy.
** @return Start of the destination memory.
** @ingroup mem
*/

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const unsigned char *restrict	s8 = (const unsigned char *)src + n;
	unsigned char *restrict			d8;
	const size_t *restrict			s64 = (const size_t *)(src + n);
	size_t *restrict				d64;
	register size_t					i;

	d8 = (unsigned char *)dst + n;
	d64 = (size_t *)(dst + n);
	if (dst == src)
		return (dst);
	else if (dst - src >= (long long)n)
		return (ft_memcpy(dst, src, n));
	i = 0;
	while (i < (n / sizeof(size_t)))
	{
		*--d64 = *--s64;
		i++;
	}
	d8 -= i * sizeof(size_t);
	s8 -= i * sizeof(size_t);
	i = n % sizeof(size_t);
	while (i--)
		*--d8 = *--s8;
	return (dst);
}
