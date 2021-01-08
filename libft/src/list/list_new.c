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

#include "list.h"
#include "mem.h"

t_list		*list_new(void)
{
	return ((t_list *)ft_calloc(1, sizeof(t_list)));
}

t_list_node	*list_new_node(void *data)
{
	t_list_node	*node;

	node = (t_list_node	*)ft_calloc(1, sizeof(t_list_node));
	node->data = data;
	return (node);
}
