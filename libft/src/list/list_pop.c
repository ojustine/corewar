/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:59:49 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"

static void	*pop_front_half(t_list *list, size_t index)
{
	t_list_node		*node;
	void			*data;
	register size_t	i;

	i = 1;
	node = list->front->next;
	while (i < index)
	{
		node = node->next;
		i++;
	}
	node->prev->next = node->next;
	node->next->prev = node->prev;
	list->size--;
	data = node->data;
	free(node);
	return (data);
}

static void	*pop_back_half(t_list *list, size_t index)
{
	t_list_node		*node;
	void			*data;
	register size_t	i;

	i = list->size - 2;
	node = list->back->prev;
	while (i > index)
	{
		node = node->prev;
		i--;
	}
	node->prev->next = node->next;
	node->next->prev = node->prev;
	list->size--;
	data = node->data;
	free(node);
	return (data);
}

void	*list_pop(t_list *list, size_t index)
{
	if (index >= list->size)
		return (NULL);
	if (index == 0)
		return (list_pop_front(list));
	if (index == list->size - 1)
		return (list_pop_back(list));
	if (index < list->size / 2)
		return (pop_front_half(list, index));
	else
		return (pop_back_half(list, index));
}

void	*list_pop_back(t_list *list)
{
	t_list_node	*node;
	void		*data;

	if (list->size == 0)
		return (NULL);
	if (list->front == list->back)
		list->front = NULL;
	else if (list->front->next == list->back)
		list->front->next = NULL;
	node = list->back;
	list->back = node->prev;
	if (list->back != NULL)
		list->back->next = NULL;
	--list->size;
	data = node->data;
	free(node);
	return (data);
}

void	*list_pop_front(t_list *list)
{
	t_list_node	*node;
	void		*data;

	if (list->size == 0)
		return (NULL);
	if (list->back == list->front)
		list->back = NULL;
	else if (list->back->prev == list->front)
		list->back->prev = NULL;
	node = list->front;
	list->front = node->next;
	if (list->front != NULL)
		list->front->prev = NULL;
	--list->size;
	data = node->data;
	free(node);
	return (data);
}
