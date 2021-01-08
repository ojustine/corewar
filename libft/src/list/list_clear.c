/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:59:49 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"

void	list_clear(t_list **list, void (*f)(void *))
{
	t_list_node	*node;
	t_list_node	*tmp;

	if (!list)
		return ;
	node = (*list)->front;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		if (f)
			f(tmp->data);
		free(tmp);
	}
	free(*list);
	list = NULL;
}
