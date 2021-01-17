#ifndef LOGGER__H
# define LOGGER__H

# include "logger.h"
# include "hash_map.h"

struct					s_appender
{
	enum e_log_level	log_lvl;
	char				*name;
	char				*path;
	int					fd;
	int					enabled;
};

struct					s_logger
{
	enum e_log_level	log_lvl;
	t_appender			*stdout_app;
	t_appender			*stderr_app;
	t_hashmap			*file_apps;
	unsigned			flags;
};

void					logger_init_storage(void);
void					logger_free_app(void *app);
t_appender				*logger_get_app(const char *name);
void					do_log(enum e_log_level log_lvl, const char *func,
						const char *fmt, va_list ap);

#endif
