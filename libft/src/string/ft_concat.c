#include <stdarg.h>
#include <stdlib.h>
#include "error.h"
#include "util.h"
#include "mem.h"
#include "str.h"

static size_t	total_len(size_t count, va_list *ap)
{
	size_t	len;

	len = 0;
	while (count--)
		len += ft_strlen(va_arg(*ap, char *));
	return (len);
}

char			*ft_concat(size_t count, ...)
{
	va_list	ap;
	char	*res;
	char	*tmp;
	size_t	len;
	size_t	null_pos;

	va_start(ap, count);
	len = total_len(count, &ap);
	va_end(ap);
	res = (char *)malloc(sizeof(char) * (len + 1));
	ft_assert(res != NULL, __func__, E_ALLOC);
	null_pos = 0;
	va_start(ap, count);
	while (count--)
	{
		tmp = va_arg(ap, char*);
		len = ft_strlen(tmp);
		ft_memcpy(res + null_pos, tmp, len);
		null_pos += len;
	}
	va_end(ap);
	res[null_pos] = '\0';
	return (res);
}
