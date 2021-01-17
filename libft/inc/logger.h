#ifndef LOGGER_H
# define LOGGER_H

#include <stdarg.h>

# define				L_STDOUT		"stdout"
# define				L_STDERR		"stderr"
# define				L_FILE_NAME_MAX	256
# define				L_DATETIME_MAX	64
# define				L_DATETIME_PATT	"%Y-%m-%d %H:%M:%S"
# define				L_FILE_PATT		"%Y-%m-%d"
# define				L_LOG_EXT		".log"
# define				L_ENABLE		1
# define				L_DISABLE		0
# define				L_PREFIX_ALL	"[ALL]"
# define				L_PREFIX_TRACE	"[TRACE]"
# define				L_PREFIX_DEBUG	"[DEBUG]"
# define				L_PREFIX_INFO	"[INFO]"
# define				L_PREFIX_WARN	"[WARN]"
# define				L_PREFIX_ERROR	"[ERROR]"
# if defined(__MACH__) || defined(linux) || defined(_POSIX_VERSION)
#  define				L_CLR_RESET		"\033[0m"
#  define				L_CLR_TRACE		"\x1B[90m"
#  define				L_CLR_DEBUG		"\x1B[32m"
#  define				L_CLR_INFO		"\x1B[37m"
#  define				L_CLR_WARN		"\x1B[33m"
#  define				L_CLR_ERROR		"\x1B[31m"
# else
#  define				L_CLR_RESET		""
#  define				L_CLR_TRACE		""
#  define				L_CLR_DEBUG		""
#  define				L_CLR_INFO		""
#  define				L_CLR_WARN		""
#  define				L_CLR_ERROR		""
# endif

enum					e_logger_config_flags
{
	L_USE_STDOUT = (1U),
	L_USE_STDERR = (1U << 1),
	L_USE_COLORS = (1U << 2),
	L_SHOW_PREFIX = (1U << 3),
	L_SHOW_TIME = (1U << 4),
	L_SHOW_FUNC = (1U << 5),
	L_FILE_SPEC = (1U << 6),
	L_FILE_APPEND = (1U << 7),
	L_STD_CFG = L_USE_STDOUT | L_SHOW_PREFIX | L_SHOW_TIME | L_SHOW_FUNC | L_FILE_APPEND
};

enum					e_log_level
{
	ALL = 0,
	TRACE,
	DEBUG,
	INFO,
	WARN,
	ERROR,
	OFF
};

typedef struct			s_appender t_appender;
typedef struct			s_logger t_logger;
extern t_logger			g_logger;

void					logger_add_app(const char *name, const char *path,
						enum e_log_level log_lvl);

void					logger_set_log_lvl(enum e_log_level log_lvl);
void					logger_switch_flags(unsigned flags, int state);
void					logger_switch_app(const char *name, int state);
void					logger_set_app_log_lvl(const char *name,
						enum e_log_level log_lvl);

void					log_msg(enum e_log_level log_lvl, const char *func,
						const char *fmt, ...);
void					log_trace(const char *func,	const char *fmt, ...);
void					log_debug(const char *func,	const char *fmt, ...);
void					log_info(const char *func,	const char *fmt, ...);
void					log_warn(const char *func,	const char *fmt, ...);
void					log_error(const char *func,	const char *fmt, ...);

void					logger_close(void);

#endif
