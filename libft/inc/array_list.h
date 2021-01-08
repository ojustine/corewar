/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:58:01 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_LIST_H
# define ARRAY_LIST_H

# include <stddef.h>

# define ARRLIST_ERR_INDEX "Array list index out of bounds"
# define ARRLIST_ERR_NULL_PTR "Array list null pointer"
# define ARRLIST_ERR_ALLOC "Array list memory alloc error"
# define ARRLIST_ERR_OUT_OF_MEM "Array list out of memory"

typedef struct		s_arrlisti
{
	int				*storage;
	size_t			capacity;
	size_t			size;
}					t_arrlisti;

typedef struct		s_arrlist
{
	void			**storage;
	size_t			capacity;
	size_t			size;
}					t_arrlist;

t_arrlisti			*arrlisti_new(size_t capacity);
int					arrlisti_push(t_arrlisti *list, int n, size_t inx);
int					arrlisti_push_front(t_arrlisti *list, int n);
int					arrlisti_push_back(t_arrlisti *list, int n);
int					arrlisti_pop(t_arrlisti *list, int *ret, size_t inx);
int					arrlisti_pop_front(t_arrlisti *list, int *ret);
int					arrlisti_pop_back(t_arrlisti *list, int *ret);
int					arrlisti_peek(t_arrlisti *list, int *ret, size_t inx);
int					arrlisti_peek_front(t_arrlisti *list, int *ret);
int					arrlisti_peek_back(t_arrlisti *list, int *ret);
int					arrlisti_ensure_capacity(t_arrlisti *list, size_t cap);
int					arrlisti_is_empty(t_arrlisti *list);

t_arrlist			*arrlist_new(size_t capacity);
int					arrlist_push(t_arrlist *list, void *data, size_t inx);
int					arrlist_push_front(t_arrlist *list, void *data);
int					arrlist_push_back(t_arrlist *list, void *data);
void				*arrlist_peek(t_arrlist *list, size_t inx);
void				*arrlist_peek_front(t_arrlist *list);
void				*arrlist_peek_back(t_arrlist *list);
void				*arrlist_pop(t_arrlist *list, size_t inx);
void				*arrlist_pop_front(t_arrlist *list);
void				*arrlist_pop_back(t_arrlist *list);
void				arrlist_ensure_capacity(t_arrlist *list, size_t cap);
int					arrlist_is_empty(t_arrlist *list);

#endif
