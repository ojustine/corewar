/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:59:10 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_MAP_H
# define HASH_MAP_H

# include <stdint.h>
# include <stddef.h>

typedef struct		s_hashmap_entry
{
	void			*key;
	void			*val;
	size_t			key_len;
	size_t			offset;
	uint64_t		hash;
}					t_hashmap_entry;

typedef struct		s_hashmap
{
	size_t			size;
	size_t			capacity;
	size_t			max_size;
	size_t			max_offset;
	float			load_factor;
	uint64_t		hash_key;
	t_hashmap_entry	*storage;
}					t_hashmap;

uint64_t			murmur_hash_64(const void *key, size_t len, uint32_t seed);
size_t				ft_log2(size_t n);
size_t				next_power_of_two(size_t n);
t_hashmap			*hashmap_new(void);
t_hashmap			*hashmap_new_param(size_t capacity, float load_factor,
					size_t hash_key);
int					hashmap_resize(t_hashmap *hmap, size_t new_capacity);
int					hashmap_put(t_hashmap *hmap, const void *key,
					size_t key_len, void *val);
void				*hashmap_get(t_hashmap *hmap, const void *key,
					size_t key_len);
int					hashmap_insert(t_hashmap *hmap, t_hashmap_entry *entry);
void				*hashmap_iter(t_hashmap *hmap, size_t *iter, void **keyp,
					void **valp);
void				hashmap_destroy(t_hashmap **hmap);
#endif
