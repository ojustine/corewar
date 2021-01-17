#include "logger.h"

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

}
