#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

int					ft_sprintf(char *str, const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vsprintf(str, format, ap);
	va_end(ap);
	return (ret);
}

int					ft_snprintf(char *str, size_t maxlen,
					const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vsnprintf(str, maxlen, format, ap);
	va_end(ap);
	return (ret);
}

int					ft_vprintf(const char *format, va_list ap)
{
	return (ft_vdprintf(STDOUT_FILENO, format, ap));
}

int					ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (ret);
}

int					ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vdprintf(STDOUT_FILENO, format, ap);
	va_end(ap);
	return (ret);
}
