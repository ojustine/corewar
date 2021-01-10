#ifndef LOGGER_H
# define LOGGER_H

# include "hash_map.h"

/*
**
*/
# define				LOG_SHOW_PREFIX	0x1
# define				LOG_SHOW_TIME	0x2
# define				LOG_SHOW_NAME	0x4
# define				LOG_SHOW_FUNC	0x8

# define				LOG_ADD_STDOUT	0xa
# define				LOG_ADD_STDERR	0xa

enum					e_log_level
{
	ALL,
	TRACE,
	DEBUG,
	INFO,
	WARN,
	ERROR,
	OFF
};

typedef struct			s_appender
{
	enum e_log_level	log_level;
	char				*name;
	char				*path;
	int					fd;
}						t_appender;

typedef struct			s_logger
{
	t_hash_map			*appenders;
}						t_logger;

static const t_appender	g_stdout_appender = {
	.log_level = ERROR,
	.name = "stdout",
	.path = "",
	.fd = 1
};

static const t_appender	g_stderr_appender = {
	.log_level = ERROR,
	.name = "stderr",
	.path = "",
	.fd = 2
};

#endif
