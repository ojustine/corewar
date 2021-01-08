/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrlist_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:14:46 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "array_list.h"
#include "mem.h"
#include "util.h"

void	arrlist_ensure_capacity(t_arrlist *list, size_t cap)
{
	size_t	new_cap;
	void	**storage;

	ft_assert(list != NULL, __func__, ARRLIST_ERR_NULL_PTR);
	if (cap > list->capacity)
	{
		new_cap = list->capacity;
		while ((new_cap = new_cap * 3 / 2 + 1) < cap)
			;
		ft_assert(new_cap < SIZE_MAX / sizeof(void *), __func__,
		ARRLIST_ERR_OUT_OF_MEM);
		storage = malloc(new_cap * sizeof(void *));
		ft_assert(list != NULL, __func__, ARRLIST_ERR_ALLOC);
		ft_memcpy(storage, list->storage, list->size * sizeof(void *));
		ft_bzero((void *)storage + list->size * sizeof(void *),
		(new_cap - list->size) * sizeof(void *));
		free(list->storage);
		list->storage = storage;
		list->capacity = new_cap;
	}
}

int		arrlist_is_empty(t_arrlist *list)
{
	ft_assert(list != NULL, __func__, ARRLIST_ERR_NULL_PTR);
	return (!list->size);
}
