#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <hash_map.h>
#include <mem.h>
#include "regex_.h"

#define LITTLE_ENDIAN 0
#define BIG_ENDIAN    1

int endian() {
	int i = 1;
	char *p = (char *)&i;

	if (p[0] == 1)
		return LITTLE_ENDIAN;
	else
		return BIG_ENDIAN;
}

int main()
{
	char tab[1000];
	ft_bzero(tab, sizeof(tab));

	re_comp("\\(A+.Z\\)");
	printf("%d\n", re_exec("ASZ"));
	printf("%d\n", re_exec("AOZ"));
	re_subs("\\1fgrfg\\1\\2", tab);
	printf("%s", tab);
}
