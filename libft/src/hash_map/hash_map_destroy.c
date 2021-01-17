/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:22:40 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash_map.h"

void	hashmap_destroy(t_hashmap **hmap, void (*f)(void *))
{
	register size_t				i;
	register t_hashmap_entry	*entry;

	if (!hmap)
		return ;
	i = 0;
	while (i < (const size_t)(*hmap)->capacity)
	{
		entry = &(*hmap)->storage[i++];
		if (entry->key)
		{
			free(entry->key);
			if (f)
				f(entry->val);
		}
	}
	free((*hmap)->storage);
	free(*hmap);
	*hmap = NULL;
}
