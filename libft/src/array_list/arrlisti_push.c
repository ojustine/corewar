/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrlisti_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:14:46 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_list.h"
#include "mem.h"

int		arrlisti_push(t_arrlisti *list, int n, size_t inx)
{
	if (!list || !arrlisti_ensure_capacity(list, list->size + 1))
		return (0);
	ft_memmove(&list->storage[inx + 1], &list->storage[inx],
				(list->size - inx) * sizeof(int));
	list->storage[inx] = n;
	list->size++;
	return (1);
}

int		arrlisti_push_front(t_arrlisti *list, int n)
{
	return (arrlisti_push(list, n, 0));
}

int		arrlisti_push_back(t_arrlisti *list, int n)
{
	if (!list || !arrlisti_ensure_capacity(list, list->size + 1))
		return (0);
	list->storage[list->size] = n;
	list->size++;
	return (1);
}
