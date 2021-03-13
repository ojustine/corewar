#ifndef STRBUILDER__H
#define STRBUILDER__H

#include "str.h"
#include "list.h"

struct					s_strbuilder
{
	char				*name;
	char				*path;
	int					fd;
	int					enabled;
};

#endif
