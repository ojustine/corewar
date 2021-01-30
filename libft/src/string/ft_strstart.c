#include "str.h"

int	ft_strstart(const char *str, const char *prefix)
{
	return (ft_strnequ(str, prefix, ft_strlen(prefix)));
}
