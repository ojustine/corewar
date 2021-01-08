/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrlisti_utils.c                                   :+:      :+:    :+:   */
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

int		arrlisti_ensure_capacity(t_arrlisti *list, size_t cap)
{
	size_t			new_cap;
	int				*storage;

	if (!list)
		return (0);
	if (cap > list->capacity)
	{
		new_cap = list->capacity;
		while ((new_cap = new_cap * 3 / 2 + 1) < cap)
			;
		if (new_cap >= SIZE_MAX / sizeof(int))
			return (0);
		storage = malloc(new_cap * sizeof(int));
		if (!storage)
			return (0);
		ft_memcpy(storage, list->storage, list->size * sizeof(int));
		ft_bzero((void *)storage + list->size * sizeof(int),
				(new_cap - list->size) * sizeof(int));
		free(list->storage);
		list->storage = storage;
		list->capacity = new_cap;
	}
	return (1);
}

int		arrlisti_is_empty(t_arrlisti *list)
{
	if (!list)
		return (-1);
	return (!list->size);
}
