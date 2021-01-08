/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrlisti_new.c                                     :+:      :+:    :+:   */
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

t_arrlisti	*arrlisti_new(size_t capacity)
{
	t_arrlisti	*list;

	if (!capacity || capacity > SIZE_MAX / sizeof(int))
		return (NULL);
	list = malloc(sizeof(t_arrlisti));
	if (!list)
		return (NULL);
	list->size = 0;
	list->capacity = capacity;
	list->storage = malloc(capacity * sizeof(int));
	if (!list->storage)
	{
		free(list);
		return (NULL);
	}
	ft_bzero(list->storage, capacity * sizeof(int ));
	return (list);
}
