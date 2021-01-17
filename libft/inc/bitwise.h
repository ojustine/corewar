#ifndef BITWISE_H
# define BITWISE_H

# include <stddef.h>

/**
* @defgroup bitwise Bitwise
* @brief Bits manipulation functions
* @details bitwise desc here!//FIXME
* @{
*/

/**
* @file operations.c
*/
size_t	and(size_t x, size_t y);
size_t	or(size_t x, size_t y);
size_t	xor(size_t x, size_t y);
size_t	not(size_t x);

/**
* @file shift.c
*/
size_t	rshift(size_t x, size_t shift);
size_t	lshift(size_t x, size_t shift);
size_t	circular_lshift(size_t x, size_t shift);
size_t	circular_rshift(size_t x, size_t shift);

/**
* @file hasbyte.c
*/
int		has_zero_byte(size_t word);
int		has_byte(size_t word, unsigned char byte);
int 	has_byte_more(size_t word, unsigned char byte);
int 	has_byte_less(size_t word, unsigned char byte);

/**
* @file mask.c
*/
size_t	get_mask(unsigned char masked);

/**
* }@
*/
#endif
