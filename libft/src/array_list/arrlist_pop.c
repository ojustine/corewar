/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrlist_pop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:14:46 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_list.h"
#include "mem.h"
#include "util.h"

void	*arrlist_pop(t_arrlist *list, size_t inx)
{
	void	*ret;

	ft_assert(list != NULL, __func__, ARRLIST_ERR_NULL_PTR);
	ft_assert(list->size != 0 && inx < list->size, __func__,
	ARRLIST_ERR_INDEX);
	ret = list->storage[inx];
	ft_memmove(&list->storage[inx], &list->storage[inx + 1],
	(list->size - inx - 1) * sizeof(void *));
	list->size--;
	return (ret);
}

void	*arrlist_pop_front(t_arrlist *list)
{
	return (arrlist_pop(list, 0));
}

void	*arrlist_pop_back(t_arrlist *list)
{
	ft_assert(list != NULL, __func__, ARRLIST_ERR_NULL_PTR);
	ft_assert(list->size != 0, __func__, ARRLIST_ERR_INDEX);
	list->size--;
	return (list->storage[list->size]);
}
