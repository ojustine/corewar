#include <stdarg.h>
#include <time.h>
#include "str.h"
#include "ft_printf.h"
#include "logger_.h"
#include "logger.h"

static const char		*g_logger_prefix[OFF - ALL] = {
		L_PREFIX_ALL,
		L_PREFIX_TRACE,
		L_PREFIX_DEBUG,
		L_PREFIX_INFO,
		L_PREFIX_WARN,
		L_PREFIX_ERROR
};
static const char		*g_logger_colors[OFF - ALL] = {
		L_CLR_RESET,
		L_CLR_TRACE,
		L_CLR_DEBUG,
		L_CLR_INFO,
		L_CLR_WARN,
		L_CLR_ERROR
};

static void	log_func(int fd, const char *func)//ft_dprintf(app->fd, "%.80s: ", func);
{
	static const char	*spaces = "                              ";
	static size_t		max = 0;
	const size_t		flen = ft_strlen(func);

	max = (max > flen ? max : flen);
	ft_dprintf(fd, "%.30s:%.*s", func, max - flen + 1, spaces);
}

static void	log_prefix(enum e_log_level log_lvl, const char *func,
			t_appender *app)
{
	char		date[L_DATETIME_MAX + 1];
	time_t		raw_time;
	struct tm	*timeval;

	if (g_logger.flags & L_USE_COLORS && app->fd < 3)
		ft_dprintf(app->fd, g_logger_colors[log_lvl]);
	if (g_logger.flags & L_SHOW_PREFIX)
		ft_dprintf(app->fd, "%-7.5s", g_logger_prefix[log_lvl]);
	if (g_logger.flags & L_SHOW_TIME)
	{
		time(&raw_time);
		timeval = localtime(&raw_time);
		date[strftime(date, L_DATETIME_MAX, L_DATETIME_PATT, timeval)] = '\0';
		ft_dprintf(app->fd, "%.*s ", L_DATETIME_MAX, date);
	}
	if (g_logger.flags & L_SHOW_FUNC && func)
		log_func(app->fd, func);
}

static void	log_line(int fd, const char *fmt, va_list ap)
{
	ft_vdprintf(fd, fmt, ap);
	ft_dprintf(fd, "\n");
	if (g_logger.flags & L_USE_COLORS && fd < 3)
		ft_dprintf(fd, L_CLR_RESET);
}

void		do_log(enum e_log_level log_lvl, const char *func, const char *fmt,
			va_list ap)
{
	t_appender	*app;
	size_t		i;
	int			stderr_not_used;

	if (log_lvl < g_logger.log_lvl)
		return ;
	i = 0;
	stderr_not_used = 1;
	app = g_logger.stdout_app;
	while (app)
	{
		if (app && app->enabled && log_lvl >= app->log_lvl)
		{
			log_prefix(log_lvl, func, app);
			log_line(app->fd, fmt, ap);
		}
		if (stderr_not_used-- == 1)
			app = g_logger.stderr_app;
		else if (g_logger.file_apps != NULL)
			hashmap_iter(g_logger.file_apps, &i, NULL, (void **)&app);
		else
			app = NULL;
	}
}

void		log_msg(enum e_log_level log_lvl, const char *func,
			const char *fmt, ...)
{
	va_list	ap;

	if (log_lvl <= ALL || log_lvl >= OFF)
	{
		log_msg(ERROR, __func__, "Incorrect log level value: '%d'", log_lvl);
		return ;
	}
	va_start(ap, fmt);
	do_log(log_lvl, func, fmt, ap);
	va_end(ap);
}

