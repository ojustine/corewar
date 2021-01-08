/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:26:39 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "mem.h"
#include "hash_map.h"

static inline int	hashmap_insert_try(t_hashmap *hmap, t_hashmap_entry *bucket,
					t_hashmap_entry *entry)
{
	t_hashmap_entry	tmp;

	if (!bucket->key)
	{
		*bucket = *entry;
		hmap->size++;
		return (1);
	}
	if (bucket->hash == entry->hash && bucket->key_len == entry->key_len &&
		ft_memcmp(bucket->key, entry->key, entry->key_len) == 0)
	{
		free(entry->key);
		bucket->val = entry->val;
		return (1);
	}
	if (entry->offset > bucket->offset)
	{
		tmp = *entry;
		*entry = *bucket;
		*bucket = tmp;
	}
	return (0);
}

int					hashmap_insert(t_hashmap *hmap, t_hashmap_entry *entry)
{
	t_hashmap_entry *bucket;
	register size_t	i;

	entry->hash = murmur_hash_64(entry->key, entry->key_len, hmap->hash_key);
	entry->offset = 0;
	i = entry->hash * hmap->hash_key & (hmap->capacity - 1);
	while (entry->offset <= hmap->max_offset)
	{
		bucket = &hmap->storage[i];
		if (hashmap_insert_try(hmap, bucket, entry))
			return (1);
		if (++i == hmap->capacity)
			i = 0;
		entry->offset++;
	}
	return (0);
}

int					hashmap_put(t_hashmap *hmap, const void *key,
					size_t key_len, void *val)
{
	size_t			try;
	t_hashmap_entry	entry;

	if (!key || !key_len)
		return (0);
	entry.key = malloc(key_len);
	ft_assert(entry.key != NULL, __func__, "malloc error");
	ft_memcpy(entry.key, key, key_len);
	entry.key_len = key_len;
	entry.val = val;
	try = 0;
	while (hmap->size >= hmap->max_size || !hashmap_insert(hmap, &entry))
	{
		if (!hashmap_resize(hmap, hmap->capacity << 1U))
		{
			try++;
		}
	}
	return (0);
}
