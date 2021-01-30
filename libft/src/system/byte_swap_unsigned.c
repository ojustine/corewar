#include <stdint.h>
#include "mem.h"
#include "logger.h"

void		byte_swap(void *pv, size_t size)
{
	size_t lo;
	size_t hi;
	t_byte *p;
	t_byte tmp;

	if (size == 0)
	{
		log_warn(__func__, "Zero size will result an infinite loop. Skipped");
		return ;
	}
	p = (t_byte *)pv;
	lo = 0;
	hi = size - 1;
	while (hi > lo)
	{
		tmp = p[lo];
		p[lo] = p[hi];
		p[hi] = tmp;
		lo++;
		hi--;
	}
}

uint16_t	byte_swap_u16(uint16_t val)
{
	return ((val << 8) | (val >> 8));
}

uint32_t	byte_swap_u32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return ((val << 16) | (val >> 16));
}

uint64_t	byte_swap_u64(uint64_t val)
{
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL)
		| ((val >> 8) & 0x00FF00FF00FF00FFULL);
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL)
		| ((val >> 16) & 0x0000FFFF0000FFFFULL);
	return ((val << 32) | (val >> 32));
}
