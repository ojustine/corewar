/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:30:59 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mem.h"

/*
** @brief Allocate dynamic memory.
** @details The ft_calloc() function allocates memory for an array of @a n_elem
** of @a elem_size bytes each. The memory is set to zero.
** @param [in] n_elem Number of elements.
** @param [in] elem_size Size of each element.
** @return Start of the allocated memory or NULL in case of error.
** @see ft_bzero()
** @ingroup mem
*/

void	*ft_calloc(size_t n_elem, size_t elem_size)
{
	void			*mem;
	const size_t	full_size = n_elem * elem_size;

	if (!full_size || (elem_size && n_elem > SIZE_MAX / elem_size))
		return (NULL);
	mem = (void*)malloc(full_size);
	if (!mem)
		return (NULL);
	return (ft_bzero(mem, full_size));
}

/*
** @brief Allocate dynamic memory.
** @details The ft_memalloc() function allocates memory of @a size bytes.
** The memory is set to zero.
** @param [in] size Size of memory to allocate.
** @return Start of the allocated memory or NULL in case of error.
** @see ft_bzero()
** @ingroup mem
*/

void	*ft_memalloc(size_t size)
{
	void *mem;

	if (size + 1 == 0)
		return (NULL);
	mem = (void*)malloc(size);
	if (!mem)
		return (NULL);
	return (ft_bzero(mem, size));
}
