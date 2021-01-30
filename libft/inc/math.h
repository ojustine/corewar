/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 21:08:30 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include <stddef.h>

/**
* @defgroup math Math
* @brief Math functions and constants
* @details Math desc here!//FIXME
* @{
*/

#include <stdint.h>

/**
* @file abs.c
*/
unsigned			math_abs(int num);
unsigned long		math_labs(long num);
unsigned long long	math_llabs(long long num);

/**
* @file divmod.c
*/
int					math_divmod(int dividend, int divisor, int *remainder);
long				math_ldivmod(long dividend, long divisor, long *remainder);
long long			math_lldivmod(long long dividend, long long divisor,
					long long *remainder);
/**
* @file moddiv.c
*/
int					math_moddiv(int dividend, int divisor,
					int *quotient);
long				math_lmoddiv(long dividend, long divisor, long *quotient);
long long			math_llmoddiv(long long dividend, long long divisor,
					long long *quotient);
/**
* @file pow.c
*/
double				math_pow(double base, int n);
float				math_fpow(float base, int n);
long double			math_lpow(long double base, int n);

/**
* @file sqrt.c
*/
int					math_floor_sqrt(int n);

/**
* @file min.c
*/
int					math_min(int a, int b);

/**
* @file min.c
*/
int					math_max(int a, int b);

/**
* @file numlen.c
*/
size_t				math_intlen(register int32_t n);
size_t				math_longlen(register int64_t n);

/**
* }@
*/
#endif
