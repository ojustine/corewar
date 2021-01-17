#include <stdio.h>
#include <util.h>
#include <fcntl.h>
#include <stdlib.h>
#include "error.h"
#include "logger_.h"
#include "logger.h"

t_appender	g_stdout_appender = {
		.log_lvl = INFO,
		.name = L_STDOUT,
		.path = "",
		.fd = STDOUT_FILENO,
		.enabled = L_ENABLE
};

t_appender	g_stderr_appender = {
		.log_lvl = ERROR,
		.name = L_STDERR,
		.path = "",
		.fd = STDERR_FILENO,
		.enabled = L_DISABLE
};

t_logger	g_logger = {
		.log_lvl = ALL,
		.stdout_app = &g_stdout_appender,
		.stderr_app = &g_stderr_appender,
		.file_apps = NULL,
		.flags = L_STD_CFG
};

void	logger_init_storage(void)
{
	if (g_logger.file_apps != NULL)
		return ;
	g_logger.file_apps = hashmap_new_param(8, 0.8f, 37);
	ft_assert(g_logger.file_apps != NULL, __func__, E_ALLOC);
}

void	logger_free_app(void *app)
{
	t_appender	*appender;

	appender = (t_appender *)app;
	if (!appender)
		return ;
	close(appender->fd);
	free(appender->name);
	free(appender->path);
	free(appender);
}

void	logger_close(void)
{
	if (g_logger.file_apps)
		hashmap_destroy(&g_logger.file_apps, logger_free_app);
}
