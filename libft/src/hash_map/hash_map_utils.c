/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:09:56 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "hash_map.h"

#define MAGIC	0xc6a4a7935bd1e995ULL
#define ROTATE	47U

static inline uint64_t	murmur_tail(const unsigned char *tail, size_t len,
						uint64_t hash)
{
	if (len > 6)
		hash ^= (uint64_t)tail[6] << 48U;
	if (len > 5)
		hash ^= (uint64_t)tail[5] << 40U;
	if (len > 4)
		hash ^= (uint64_t)tail[4] << 32U;
	if (len > 3)
		hash ^= (uint64_t)tail[3] << 24U;
	if (len > 2)
		hash ^= (uint64_t)tail[2] << 16U;
	if (len > 1)
		hash ^= (uint64_t)tail[1] << 8U;
	if (len > 0)
	{
		hash ^= (uint64_t)tail[0];
		hash *= MAGIC;
	}
	return (hash);
}

uint64_t				murmur_hash_64(const void *key, size_t len,
						uint32_t seed)
{
	uint64_t		tmp;
	uint64_t		hash;
	const uint64_t	*data = (const uint64_t *)key;
	const uint64_t	*end = data + (len / 8);

	hash = seed ^ (len * MAGIC);
	while (data != end)
	{
		tmp = *data++;
		tmp *= MAGIC;
		tmp ^= tmp >> ROTATE;
		tmp *= MAGIC;
		hash ^= tmp;
		hash *= MAGIC;
	}
	hash = murmur_tail((const unsigned char *)data, len % 8, hash);
	hash ^= hash >> ROTATE;
	hash *= MAGIC;
	hash ^= hash >> ROTATE;
	return (hash);
}

size_t					ft_log2(size_t n)
{
	static int8_t table[64] = {
		63, 0, 58, 1, 59, 47, 53, 2,
		60, 39, 48, 27, 54, 33, 42, 3,
		61, 51, 37, 40, 49, 18, 28, 20,
		55, 30, 34, 11, 43, 14, 22, 4,
		62, 57, 46, 52, 38, 26, 32, 41,
		50, 36, 17, 19, 29, 10, 13, 21,
		56, 45, 25, 31, 35, 16, 9, 12,
		44, 24, 15, 8, 23, 7, 6, 5
	};

	if (n < 2)
		return (0);
	n |= n >> 1U;
	n |= n >> 2U;
	n |= n >> 4U;
	n |= n >> 8U;
	n |= n >> 16U;
	n |= n >> 32U;
	return (table[((n - (n >> 1U)) * 0x07edd5e59a4e28c2) >> 58U]);
}

size_t					next_power_of_two(size_t n)
{
	if (n < 2)
		n = 2;
	--n;
	n |= n >> 1U;
	n |= n >> 2U;
	n |= n >> 4U;
	n |= n >> 8U;
	n |= n >> 16U;
	n |= n >> 32U;
	++n;
	return (n);
}

size_t					hash_map_calc_index(t_hashmap *hmap, uint64_t hash)
{
	return (hash * hmap->hash_key % hmap->size);
}
