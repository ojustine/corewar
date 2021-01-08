/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:56:52 by ojustine          #+#    #+#             */
/*   Updated: 2020/03/04 13:56:53 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "str.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	register char			*res;
	register const char		*src1 = s1;
	register const char		*src2 = s2;
	register const size_t	len1 = ft_strlen(src1);
	register const size_t	len2 = ft_strlen(src2);

	if (src1 == NULL || src2 == NULL)
		return (NULL);
	res = malloc(len1 + len2 + 1);
	if (res)
	{
		ft_memcpy(res, src1, len1);
		ft_memcpy(res + len1, src2, len2 + 1);
	}
	return (res);
}
