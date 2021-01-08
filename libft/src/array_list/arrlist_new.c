/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrlist_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:04:17 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mem.h"
#include "util.h"
#include "array_list.h"

t_arrlist	*arrlist_new(size_t capacity)
{
	t_arrlist	*list;

	if (!capacity)
		return (NULL);
	ft_assert(capacity < SIZE_MAX / sizeof(void *), __func__,
	ARRLIST_ERR_OUT_OF_MEM);
	list = malloc(sizeof(t_arrlist));
	ft_assert(list != NULL, __func__, ARRLIST_ERR_ALLOC);
	list->size = 0;
	list->capacity = capacity;
	list->storage = malloc(capacity * sizeof(void *));
	ft_assert(list->storage != NULL, __func__, ARRLIST_ERR_ALLOC);
	ft_bzero(list->storage, capacity * sizeof(void *));
	return (list);
}
