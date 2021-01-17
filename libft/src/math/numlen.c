#include <stdint.h>

size_t	math_intlen(register int32_t n)
{
	static const int32_t	sizes[10] = {9, 99, 999, 9999, 99999, 999999,
							9999999, 99999999, 999999999, INT32_MAX};
	register size_t			i;

	if (n < 0)
	{
		if (n == INT32_MIN)
			return (10);
		else
			n = -n;
	}
	i = 0;
	while (i++ < 11)
		if (n <= sizes[i - 1])
			return (i);
	return (10);
}

size_t	math_longlen(register int64_t n)
{
	register int64_t	rank;
	register size_t		i;

	if (n < 0)
	{
		if (n == INT64_MIN)
			return (19);
		else
			n = -n;
	}
	rank = 10;
	i = 1;
	while (i < 19)
	{
		if (n < rank)
			return (i);
		rank *= 10;
		i++;
	}
	return (19);
}
