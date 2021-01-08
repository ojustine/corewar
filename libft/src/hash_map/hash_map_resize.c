/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_resize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:59:49 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "hash_map.h"
#include "mem.h"

void	hashmap_init_new_storage(t_hashmap *hmap, size_t new_capacity)
{
	new_capacity = next_power_of_two(new_capacity);
	ft_assert(new_capacity > hmap->size, __func__, "hmap size overflow");
	hmap->storage = ft_calloc(new_capacity, sizeof(t_hashmap_entry));
	ft_assert(hmap->storage != NULL, __func__, "malloc error");
	hmap->capacity = new_capacity;
	hmap->max_size = new_capacity * hmap->load_factor;
	hmap->max_offset = ft_log2(new_capacity);
	hmap->size = 0;
}

int		hashmap_resize(t_hashmap *hmap, size_t new_capacity)
{
	register size_t				i;
	const size_t				old_capacity = hmap->capacity;
	register t_hashmap_entry	*entry;
	t_hashmap_entry				*old_storage;
	t_hashmap					snapshot;

	snapshot = *hmap;
	old_storage = hmap->storage;
	hashmap_init_new_storage(hmap, new_capacity);
	i = 0;
	while (i < old_capacity)
	{
		entry = &old_storage[i++];
		if (!entry->key)
			continue;
		if (!hashmap_insert(hmap, entry))
		{
			free(hmap->storage);
			*hmap = snapshot;
			return (0);
		}
	}
	free(old_storage);
	return (1);
}
