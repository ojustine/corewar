#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "op.h"

int main()
{
	header_t h;

	int fd = open("zork.cor", O_RDONLY);
	read(fd, &h, sizeof(header_t));
	int s = ~h.prog_size;
}
