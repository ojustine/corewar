/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:55:24 by ojustine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>

/*
** @defgroup mem Memory
** @brief Direct memory control functions
** @details Mem desc here!
** @{
*/

typedef unsigned char t_byte;

/*
** @file memalloc.c
*/
void	*ft_calloc(size_t n_elem, size_t elem_size);
void	*ft_memalloc(size_t size);

/*
** @file memcpy.c
*/
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_mempcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);

/*
** @file memchr.c
*/
void	*ft_memchr(const void *src, int c, size_t n);
void	*ft_memrchr(const void *src, int c, size_t n);

/*
** @file memswap.c
*/
void	ft_memswap(void *b1, void *b2, size_t n);

/*
** @file memset.c
*/
void	*ft_memset(void *b, int c, size_t n);
void	*ft_bzero(void *b, size_t n);

/*
** @file memcmp.c
*/
int		ft_memcmp(const void *b1, const void *b2, size_t n);

/*
** @file memmem.c
*/
void	*ft_memmem(const void *haystack, size_t hs_len,
		const void *needle, size_t ne_len);

/*
** }@
*/

#endif
