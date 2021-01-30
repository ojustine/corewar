/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:59:49 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "str.h"
#include "conv.h"

int		ft_isint(const char *str)
{
	const long long	nb = ft_atol(str);

	if (*str == '-')
		str++;
	if (*str == '\0' || (*str == '0' && *(str + 1) != '\0'))
		return (0);
	if (ft_strlen(str) > 10)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	if (nb < INT_MIN || nb > INT_MAX)
		return (0);
	return (1);
}

int		ft_isuint(const char *str)
{
	const long long	nb = ft_atol(str);

	if (*str == '\0' || (*str == '0' && *(str + 1) != '\0'))
		return (0);
	if (ft_strlen(str) > 10)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	if (nb < 0 || nb > UINT_MAX)
		return (0);
	return (1);
}
