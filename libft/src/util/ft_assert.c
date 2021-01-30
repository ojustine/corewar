/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 00:05:49 by ojustine          #+#    #+#             */
/*   Updated: 2019/09/07 18:49:45 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "util.h"
#include "logger.h"

void	ft_assert(int to_check, const char *func, const char *message)
{
	if (!to_check)
	{
		log_error(func, "Assertion failed: %s", message);
		ft_exit(SIGABRT, "Assertion error");
	}
}
