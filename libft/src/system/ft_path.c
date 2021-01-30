#include <limits.h>
#include <sys/stat.h>
#include <errno.h>
#include "system.h"
#include "mem.h"
#include "str.h"

int	ft_mkdir(const char *path)
{
#ifdef WIN32

	return (mkdir(path));
#else

	return (mkdir(path, S_IRWXU));
#endif

}

int	ft_mkpath(const char *path)
{
	const size_t	len = ft_strlen(path);
	char			fpath[PATH_MAX];
	register char	*p;

	errno = 0;
	if (len > sizeof(fpath) - 1)
	{
		errno = ENAMETOOLONG;
		return (-1);
	}
	ft_memcpy(fpath, path, len + 1);
	p = ft_memchr(fpath + 1, FILE_SEP_CHAR, len);
	while (p)
	{
		*p = '\0';
		if (ft_mkdir(fpath) != 0 && errno != EEXIST)
			return (-1);
		*p = FILE_SEP_CHAR;
		p = ft_memchr(p + 1, FILE_SEP_CHAR, len - (p - fpath));
	}
	if (ft_mkdir(fpath) != 0 && errno != EEXIST)
		return (-1);
	return (0);
}

int	ft_open_path(const char *path, int flag, mode_t mode)
{
	const size_t	len = ft_strlen(path);
	char			fpath[PATH_MAX];
	register char	*p;

	errno = 0;
	if (len > sizeof(fpath) - 1)
	{
		errno = ENAMETOOLONG;
		return (-1);
	}
	if (flag & O_CREAT)
	{
		ft_memcpy(fpath, path, len + 1);
		p = ft_memrchr(fpath, FILE_SEP_CHAR, len);
		if (p)
		{
			*p = '\0';
			if (ft_mkpath(fpath) == -1)
				return (-1);
			*p = FILE_SEP_CHAR;
		}
	}
	return (open(path, flag, mode));
}
