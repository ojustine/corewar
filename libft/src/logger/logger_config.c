#include "logger_.h"
#include "logger.h"

void	logger_switch_flags(unsigned flags, int state)
{
	if (state == L_ENABLE)
	{
		if (flags & L_USE_STDOUT)
			logger_switch_app(L_STDOUT, L_ENABLE);
		if (flags & L_USE_STDERR)
			logger_switch_app(L_STDERR, L_ENABLE);
		g_logger.flags |= flags;
	}
	else if (state == L_DISABLE)
	{
		if (flags & L_USE_STDOUT)
			logger_switch_app(L_STDOUT, L_DISABLE);
		if (flags & L_USE_STDERR)
			logger_switch_app(L_STDERR, L_DISABLE);
		g_logger.flags &= ~flags;
	}
}

void	logger_switch_app(const char *name, int state)
{
	t_appender	*app;

	app = logger_get_app(name);
	if (app)
		app->enabled = state;
	else
		log_error(__func__, "Logger: cannot find appender named: '%s'", name);
}

void	logger_set_log_lvl(enum e_log_level log_lvl)
{
	if (log_lvl >= ALL && log_lvl <= OFF)
		g_logger.log_lvl = log_lvl;
	else
		log_error(__func__, "Incorrect value of log level: '%d'", log_lvl);
}

void	logger_set_app_log_lvl(const char *name, enum e_log_level log_lvl)
{
	t_appender	*app;

	if (log_lvl >= ALL && log_lvl <= OFF)
	{
		app = logger_get_app(name);
		if (app)
			app->log_lvl = log_lvl;
		else
			log_error(__func__, "Cannot find appender named: '%s'", name);
	}
	else
		log_error(__func__, "Incorrect value of log level: '%d'", log_lvl);

}
