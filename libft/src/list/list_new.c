/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:29:18 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "util.h"
#include "list.h"
#include "mem.h"

t_list		*list_new(void)
{
	t_list	*list;

	list = (t_list *)ft_calloc(1, sizeof(t_list));
	ft_assert(list != NULL, __func__, E_ALLOC);
	return (list);
}

t_list_node	*list_new_node(void *data)
{
	t_list_node	*node;

	node = (t_list_node	*)ft_calloc(1, sizeof(t_list_node));
	ft_assert(node != NULL, __func__, E_ALLOC);
	node->data = data;
	return (node);
}
