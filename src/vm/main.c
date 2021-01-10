#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <io.h>
#include "op.h"

int main()
{
	header_t h;

	int fd = open("zork.cor", O_RDONLY);
	read(fd, &h, sizeof(header_t));

	uint32_t num = h.magic;
	uint32_t b0,b1,b2,b3;
	uint32_t res;

	b0 = (num & 0x000000ff) << 24u;
	b1 = (num & 0x0000ff00) << 8u;
	b2 = (num & 0x00ff0000) >> 8u;
	b3 = (num & 0xff000000) >> 24u;

	res = b0 | b1 | b2 | b3;

	printf("%#x", res);
}
