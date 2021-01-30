#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include "util.h"
#include "error.h"
#include "str.h"
#include "system.h"
#include "mem.h"
#include "logger_.h"
#include "logger.h"

static char			*logger_resolve_path(const char *path)
{
	const char	*orig_path = (!path || !*path) ? "." : path;
	char		*res_path;
	char		file[L_FILE_NAME_MAX + 1];
	time_t		raw_time;
	struct tm	*timeval;

	errno = 0;
	if (g_logger.flags & L_FILE_SPEC)
		res_path = ft_concat(2, orig_path, L_LOG_EXT);
	else
	{
		time(&raw_time);
		timeval = localtime(&raw_time);
		file[strftime(file, L_FILE_NAME_MAX, L_FILE_PATT, timeval)] = '\0';
		res_path = ft_concat(4, orig_path, FILE_SEP_STR, file, L_LOG_EXT);
	}
	if (!res_path)
		log_error(__func__, "Logger: memory alloc: '%m'");
	return (res_path);
}

static int			logger_open_path(const char *path)
{
	int	open_flags;
	int fd;

	open_flags = O_WRONLY | O_CREAT;
	open_flags |= (g_logger.flags & L_FILE_APPEND) ? O_APPEND : O_TRUNC;
	fd = ft_open_path(path, open_flags, 0622);
	if (fd == -1)
		log_error(__func__, "Logger: cannot open file: '%s'", path);
	return (fd);
}

static t_appender	*logger_new_app(const char *name, const char *path)
{
	t_appender	*app;

	errno = 0;
	if (logger_get_app(name))
	{
		log_error(__func__, "Logger: appender named '%s' already exists", name);
		return (NULL);
	}
	app = (t_appender *)ft_memalloc(sizeof(t_appender));
	ft_assert(app != NULL, __func__, E_ALLOC);
	if (!(app->name = ft_strdup(name)))
	{
		log_error(__func__, "Logger: cannot copy appender name");
		logger_free_app(app);
		return (NULL);
	}
	if (!(app->path = logger_resolve_path(path)))
	{
		log_error(__func__, "Logger: cannot copy appender path");
		logger_free_app(app);
		return (NULL);
	}
	return (app);
}

void				logger_add_app(const char *name, const char *path,
					enum e_log_level log_lvl)
{
	t_appender	*app;

	if (!name || !*name)
	{
		log_error(__func__, "Logger: incorrect appender name: '%s', name");
		return ;
	}
	if (!(app = logger_new_app(name, path)))
	{
		log_error(__func__, "Logger: cannot create appender: '%s'", name);
		return ;
	}
	if ((app->fd = logger_open_path(app->path)) == -1)
	{
		log_error(__func__, "Logger: cannot open file: '%s'", app->path);
		logger_free_app(app);
		return ;
	}
	app->log_lvl = log_lvl;
	app->enabled = L_ENABLE;
	logger_init_storage();
	hashmap_put(g_logger.file_apps, app->name, ft_strlen(app->name), app);
}

t_appender			*logger_get_app(const char *name)
{
	t_appender	*app;
	size_t		len;

	if (ft_strequ(name, L_STDOUT))
		app = g_logger.stdout_app;
	else if (ft_strequ(name, L_STDERR))
		app = g_logger.stderr_app;
	else if (g_logger.file_apps != NULL)
	{
		len = ft_strlen(name);
		app = (t_appender *)hashmap_get(g_logger.file_apps, name, len);
	}
	else
		app = NULL;
	return (app);
}
