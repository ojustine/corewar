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
