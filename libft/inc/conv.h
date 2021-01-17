/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:58:01 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONV_H
# define CONV_H

#include <stdint.h>

long long	ft_atol(const char *str);
size_t		ft_ultoa_base(unsigned long long value, char *buff, int base,
			int is_upper);
size_t		ft_uitoa_dec(uint32_t val, char *buff);
size_t		ft_uitoa_hex(uint32_t value, char *buff, int_fast16_t is_upper);
size_t		ft_ultoa_hex(uint64_t value, char *buff, int_fast16_t is_upper);
size_t		ft_wstrlen(const wint_t *s);

#endif
