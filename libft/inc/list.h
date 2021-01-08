/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:58:01 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stddef.h>

typedef struct			s_list_node
{
	void				*data;
	struct s_list_node	*prev;
	struct s_list_node	*next;
}						t_list_node;

typedef struct			s_list
{
	t_list_node			*back;
	t_list_node			*front;
	size_t				size;
}						t_list;

t_list					*list_new(void);
t_list_node				*list_new_node(void *data);
void					list_clear(t_list **list, void (*f)(void *));
void					*list_pop_back(t_list *list);
void					*list_pop_front(t_list *list);
void					list_push_back(t_list *list, void *item);
void					list_push_front(t_list *list, void *item);

#endif
