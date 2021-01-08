/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:57:46 by ojustine          #+#    #+#             */
/*   Updated: 2020/03/04 13:57:48 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	register const char	*tmp = s;
	register size_t		len;

	if (!s)
		return (0);
	len = 0;
	while (tmp[len] && len < maxlen)
		len++;
	return (len);
}
