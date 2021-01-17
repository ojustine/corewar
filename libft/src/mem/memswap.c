/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memswap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:30:59 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "mem.h"

static inline void	swap_8(t_byte *restrict m1, t_byte *restrict m2)
{
	const t_byte	tmp = *m1;

	*m1 = *m2;
	*m2 = tmp;
}

static inline void	swap_64(size_t *restrict m1, size_t *restrict m2)
{
	const size_t	tmp = *m1;

	*m1 = *m2;
	*m2 = tmp;
}

/*
** @brief Swaps memory.
** @details Swaps @a n bytes in two memory areas.
** @note The memory areas should not overlap.
** @param [in] b1 Memory area.
** @param [in] b2 Memory area.
** @param [in] n Size of memory to swap.
** @ingroup mem
*/

void				ft_memswap(void *b1, void *b2, size_t n)
{
	t_byte		*b1_8;
	t_byte		*b2_8;
	size_t		*b1_64;
	size_t		*b2_64;
	register	size_t	i;

	b1_8 = (t_byte *)b1;
	b2_8 = (t_byte *)b2;
	b1_64 = (size_t *)b1;
	b2_64 = (size_t *)b2;
	i = 0;
	while (i < (n / sizeof(size_t)))
	{
		swap_64(b1_64++, b2_64++);
		i++;
	}
	b1_8 += i * sizeof(size_t);
	b2_8 += i * sizeof(size_t);
	i = n % sizeof(size_t);
	while (i)
	{
		swap_8(b1_8++, b2_8++);
		i--;
	}
}
