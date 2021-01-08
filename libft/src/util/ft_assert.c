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
#include <stdlib.h>
#include "util.h"

void	ft_assert(int to_check, const char *func, const char *message)
{
	if (!to_check)
	{
		ft_log_error(message, "ASSERTION", func, NULL);
		exit(SIGABRT);
	}
}
