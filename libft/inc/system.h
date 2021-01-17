#ifndef SYSTEM_H
# define SYSTEM_H

#include <sys/stat.h>

#ifdef WIN32
#  define	FILE_SEP_CHAR	'\\'
#  define	FILE_SEP_STR	"\\"
# else
#  define	FILE_SEP_CHAR	'/'
#  define	FILE_SEP_STR	"/"
# endif

int	ft_mkdir(const char *path);
int	ft_mkpath(const char *path);
int	ft_open_path(const char *path, int flag, mode_t mode);

#endif
