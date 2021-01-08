/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:49:11 by ojustine          #+#    #+#             */
/*   Updated: 2019/09/06 17:36:55 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"

char	*ft_strchr(const char *s, int c)
{
	char *tmp;

	tmp = (char*)s;
	while (*tmp)
	{
		if ((unsigned char)*tmp == (unsigned char)c)
			return (tmp);
		tmp++;
	}
	if ((unsigned char)*tmp == '\0' && (unsigned char)c == '\0')
		return (tmp);
	return (NULL);
}
