/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrlisti_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:04:17 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_list.h"
#include "mem.h"

int	arrlisti_pop(t_arrlisti *list, int *ret, size_t inx)
{
	if (!list || list->size == 0 || inx >= list->size)
		return (0);
	if (ret)
		*ret = list->storage[inx];
	ft_memmove(&list->storage[inx], &list->storage[inx + 1],
				(list->size - inx - 1) * sizeof(int));
	list->size--;
	return (1);
}

int	arrlisti_pop_front(t_arrlisti *list, int *ret)
{
	return (arrlisti_pop(list, ret, 0));
}

int	arrlisti_pop_back(t_arrlisti *list, int *ret)
{
	if (!list || list->size == 0)
		return (0);
	if (ret)
		*ret = list->storage[list->size];
	list->size--;
	return (1);
}
