/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrlist_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:20:26 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_list.h"
#include "mem.h"
#include "util.h"

int		arrlist_push(t_arrlist *list, void *data, size_t inx)
{
	ft_assert(list != NULL, __func__, ARRLIST_ERR_NULL_PTR);
	arrlist_ensure_capacity(list, list->size + 1);
	ft_memmove(&list->storage[inx + 1], &list->storage[inx],
	(list->size - inx) * sizeof(void *));
	list->storage[inx] = data;
	list->size++;
	return (1);
}

int		arrlist_push_front(t_arrlist *list, void *data)
{
	return (arrlist_push(list, data, 0));
}

int		arrlist_push_back(t_arrlist *list, void *data)
{
	ft_assert(list != NULL, __func__, ARRLIST_ERR_NULL_PTR);
	arrlist_ensure_capacity(list, list->size + 1);
	list->storage[list->size] = data;
	list->size++;
	return (1);
}
