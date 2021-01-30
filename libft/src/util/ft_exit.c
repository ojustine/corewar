#include <stdlib.h>
#include "util.h"
#include "logger.h"

static t_ptr_exit_func	g_ptr_f[PTR_EXIT_FUNC_MAX];
static void				*g_params[PTR_EXIT_FUNC_MAX];
static const char		*g_ptr_f_msg[PTR_EXIT_FUNC_MAX];
static size_t			g_ptr_f_index;

static t_void_exit_func	g_void_f[VOID_EXIT_FUNC_MAX];
static const char		*g_void_f_msg[VOID_EXIT_FUNC_MAX];
static size_t			g_void_f_index;

void	ft_at_exit(t_void_exit_func func, const char *msg)
{
	log_debug(__func__, "Add a void func to exit: (%p)", func);
	if (g_void_f_index < VOID_EXIT_FUNC_MAX)
	{
		g_void_f[g_void_f_index] = func;
		g_void_f_msg[g_void_f_index] = msg ? msg : "No message";
		g_void_f_index++;
		log_debug(__func__,
			"Now the number of void exit functions is '%zu', max is '%d'",
			g_void_f_index, VOID_EXIT_FUNC_MAX);
	}
	else
		log_error(__func__, "Limit of void funcs exceeded: '%d'",
			VOID_EXIT_FUNC_MAX);
}

void	ft_at_exit_ptr(t_ptr_exit_func func, void *ptr, const char *msg)
{
	log_debug(__func__, "Add a parameterized func to exit: (%p):(%p)",
		func, ptr);
	if (g_ptr_f_index < PTR_EXIT_FUNC_MAX)
	{
		g_ptr_f[g_ptr_f_index] = func;
		g_params[g_ptr_f_index] = ptr;
		g_ptr_f_msg[g_ptr_f_index] = msg ? msg : "No message";
		g_ptr_f_index++;
		log_debug(__func__,
			"Now the number of parameterized functions is '%zu', max is '%d'",
			g_ptr_f_index, PTR_EXIT_FUNC_MAX);
	}
	else
		log_error(__func__, "Limit of ptr funcs exceeded: '%d'",
			PTR_EXIT_FUNC_MAX);
}

void ft_exit(int code, const char *msg)
{
	register size_t	i;

	i = 0;
	while (i < g_ptr_f_index && i < PTR_EXIT_FUNC_MAX)
	{
		log_debug(__func__, "Call a parameterized func before exit: (%p):(%p)",
			g_ptr_f[i], g_params[i]);
		log_info(__func__, "Exit function message: %s", g_ptr_f_msg[i]);
		g_ptr_f[i](g_params[i]);
		i++;
	}
	i = 0;
	while (i < g_void_f_index && i < VOID_EXIT_FUNC_MAX)
	{
		log_debug(__func__, "Call a void func before exit: (%p)", g_void_f[i]);
		log_info(__func__, "Exit function message: %s", g_void_f_msg[i]);
		g_void_f[i]();
		i++;
	}
	log_info(__func__, "Exit program with message '%s', last errno: '%m'", msg);
	exit(code);
}
