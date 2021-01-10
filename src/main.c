#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <hash_map.h>
#include "op.h"

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
//	header_t h;
//
//	int fd = open("zork.cor", O_RDONLY);
//	read(fd, &h, sizeof(header_t));
//	int s = ~h.prog_size;
	t_hashmap *h = hashmap_new();
	hashmap_put(h, "mark1", 5, "address1");
	hashmap_put(h, "mark2", 5, "address2");
	hashmap_put(h, "mark3", 5, "address3");
	printf("%s\n", hashmap_get(h, "mark4", 5));
	printf("%s\n", hashmap_get(h, "mark2", 5));
	printf("%s\n", hashmap_get(h, "mark1", 5));

	size_t i = 0;
	char *k;
	char *v;
	while (hashmap_iter(h, &i, &k, &v))
	{
		printf("%s %s\n", k, v);
	}

	hashmap_destroy(&h);
	endian();

}
