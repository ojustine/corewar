/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:07:04 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "util.h"

void	ft_kill(const char *message, const char *cause, const char *func,
		const char *file)
{
	ft_log_error(message, cause, func, file);
	exit(SIGABRT);
}
