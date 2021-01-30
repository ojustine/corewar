#include "str.h"

int	ft_strend(const char *str, const char *suffix)
{
	const size_t	str_len = ft_strlen(str);
	const size_t	suffix_len = ft_strlen(suffix);

	if (str_len < suffix_len)
		return (0);
	else
		return (ft_strequ(str + str_len - suffix_len, suffix));
}
