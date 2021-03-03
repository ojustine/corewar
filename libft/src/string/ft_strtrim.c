#include "str.h"
#include "predicates.h"

char	*ft_strtrim(const char *s)
{
	char *head;
	char *tail;

	if (!s)
		return (NULL);
	head = (char *)s;
	while (ft_isspace(*head))
		head++;
	if (*head == '\0')
		return (ft_strdup(""));
	tail = (char *)s + ft_strlen(s) - 1;
	while (tail != head && ft_isspace(*tail))
		tail--;
	return (ft_strndup(head, tail - head + 1));
}

char	*ft_strstrim(const char *s, const char *symbols)
{
	char *head;
	char *tail;

	if (!s)
		return (NULL);
	head = (char *)s;
	while (*head && ft_strchr(symbols, *head))
		head++;
	if (*head == '\0')
		return (ft_strdup(""));
	tail = (char *)s + ft_strlen(s) - 1;
	while (tail != head && ft_strchr(symbols, *tail))
		tail--;
	return (ft_strndup(head, tail - head + 1));
}
