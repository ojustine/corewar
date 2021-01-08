/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 13:34:58 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"

void	ft_log_error(const char *message, const char *cause, const char *func,
		const char *file)
{
	write(2, "ERROR: ", 7);
	if (message)
		write(2, message, ft_strlen(message));
	else
		write(2, "*null*", 6);
	if (cause)
	{
		write(2, ", CAUSE: ", 9);
		write(2, cause, ft_strlen(cause));
	}
	if (func)
	{
		write(2, ", FUNCTION: ", 12);
		write(2, func, ft_strlen(func));
	}
	if (file)
	{
		write(2, ", FILE: ", 8);
		write(2, file, ft_strlen(file));
	}
	write(2, "\n", 1);
}
