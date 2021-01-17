#include <stddef.h>
#include <limits.h>

#define ONES	((size_t)-1 / UCHAR_MAX)
#define HIGHS	(ONES * (UCHAR_MAX / 2 + 1))

/**
* @brief Determine if a @a word has a zero byte.
* @param [in] word Tested value.
* @ingroup bitwise
*/
int has_zero_byte(size_t word)
{
	return (((word - ONES) & ~word & HIGHS) != 0);
}

/**
* @brief Determine if a @a word has a byte equal to @a byte.
* @param [in] word Tested value.
* @param [in] byte Tested byte.
* @ingroup bitwise
*/
int has_byte(size_t word, unsigned char byte)
{
	const size_t	mask = word ^ (ONES * byte);

	return (((mask - ONES) & ~mask & HIGHS) != 0);
}

/**
* @brief Determine if a @a word has a byte greater then @a byte.
* @param [in] word Tested value.
* @param [in] byte Tested byte.
* @note 0 <= @a byte <= 127
* @ingroup bitwise
*/
int has_byte_more(size_t word, unsigned char byte)
{
	return (((word + ONES * ((127 - byte) | word)) & HIGHS) != 0);
}

/**
* @brief Determine if a @a word has a byte less than @a byte.
* @param [in] word Tested value.
* @param [in] byte Tested byte.
* @note 0 <= @a byte <= 128
* @ingroup bitwise
*/
int has_byte_less(size_t word, unsigned char byte)
{
	return (((word - ONES * byte) & ~word & HIGHS) != 0);
}
