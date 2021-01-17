#include <stddef.h>
#include <limits.h>

#define ONES	((size_t)-1 / UCHAR_MAX)

/**
* @brief Determine if a @a word has a zero byte.
* @param [in] word Tested value.
* @ingroup bitwise
*/
size_t	get_mask(unsigned char masked)
{
	return (masked * ONES);
}
