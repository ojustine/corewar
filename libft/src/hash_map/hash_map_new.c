/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:23:30 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash_map.h"
#include "mem.h"

/*
** add config: copy val, copy key, auto increase, auto decrease
** prime num for every pow2
*/

t_hashmap	*hashmap_new_param(size_t capacity, float load_factor,
			size_t hash_key)
{
	t_hashmap	*hmap;

	if (load_factor < 0.0f || load_factor > 0.99f)
		return (NULL);
	capacity = next_power_of_two(capacity);
	hmap = ft_calloc(1, sizeof(t_hashmap));
	if (!hmap)
		return (NULL);
	hmap->load_factor = load_factor;
	hmap->hash_key = hash_key;
	if (!hashmap_resize(hmap, capacity))
	{
		free(hmap);
		return (NULL);
	}
	return (hmap);
}

t_hashmap	*hashmap_new(void)
{
	return (hashmap_new_param(64, 0.72f, 137));
}
