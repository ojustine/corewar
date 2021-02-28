#include "mem.h"
#include "system.h"

enum e_endian endian()
{
	int i;
	char *p;

	i = 1;
	p = (char *)&i;
	if (p[0] == 1)
		return (FT_LITTLE_ENDIAN);
	else
		return (FT_BIG_ENDIAN);
}

void	*to_endian(enum e_endian to, void *pv, size_t size)
{
	uint16_t	*p16;
	uint32_t	*p32;
	uint64_t	*p64;

	if (endian() == to)
		return (pv);
	if (size == 2)
	{
		p16 = pv;
		*p16 = byte_swap_s16(*p16);
	}
	else if (size == 4)
	{
		p32 = pv;
		*p32 = byte_swap_s32(*p32);
	}
	else if (size == 8)
	{
		p64 = pv;
		*p64 = byte_swap_s32(*p64);
	}
	else
		byte_swap(pv, size);
	return (pv);
}

void	*to_sys_endian(enum e_endian from, void *pv, size_t size)
{
	uint16_t	*p16;
	uint32_t	*p32;
	uint64_t	*p64;

	if (endian() == from)
		return (pv);
	if (size == 2)
	{
		p16 = pv;
		*p16 = byte_swap_s16(*p16);
	}
	else if (size == 4)
	{
		p32 = pv;
		*p32 = byte_swap_s32(*p32);
	}
	else if (size == 8)
	{
		p64 = pv;
		*p64 = byte_swap_s32(*p64);
	}
	else
		byte_swap(pv, size);
	return (pv);
}
