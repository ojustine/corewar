#include <wctype.h>

size_t	ft_wstrlen(const wint_t *s)
{
	register size_t	len;

	len = 0;
	while (*s != L'\0')
	{
		len++;
#if WCHAR_MAX > 0xffff
		len += *s > 0xFFFF;

#endif

		len += *s > 0x7FF;
		len += *s > 0x7F;
		++s;
	}
	return (len);
}
