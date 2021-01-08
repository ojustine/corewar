/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:57:15 by ojustine          #+#    #+#             */
/*   Updated: 2020/03/04 13:57:16 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "str.h"

char	*ft_strndup(const char *s1, size_t n)
{
	register size_t	len;
	register char	*dst;
	char			*dst_begin;

	len = ft_strnlen(s1, n) + 1;
	dst = malloc(len);
	if ((dst_begin = dst) == NULL)
		return (NULL);
	dst[--len] = '\0';
	while (len > 8)
	{
		*((uint64_t*)dst) = *((uint64_t*)s1);
		dst += 8;
		s1 += 8;
		len -= 8;
	}
	while (len--)
		*dst++ = *s1++;
	return (dst_begin);
}
