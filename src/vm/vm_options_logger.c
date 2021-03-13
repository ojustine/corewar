#include "str.h"
#include "logger.h"

static int	log_level(const char *lvl)
{
	if (ft_strequ(lvl, "trace") || ft_strequ(lvl, "TRACE"))
		return (TRACE);
	else if (ft_strequ(lvl, "debug") || ft_strequ(lvl, "DEBUG"))
		return (DEBUG);
	else if (ft_strequ(lvl, "info") || ft_strequ(lvl, "INFO"))
		return (INFO);
	else if (ft_strequ(lvl, "warn") || ft_strequ(lvl, "WARN"))
		return (WARN);
	else if (ft_strequ(lvl, "error") || ft_strequ(lvl, "ERROR"))
		return (ERROR);
	return (OFF);
}

static int	is_log_level(const char *lvl)
{
	return (ft_strequ(lvl, "trace") || ft_strequ(lvl, "TRACE")
			|| ft_strequ(lvl, "debug") || ft_strequ(lvl, "DEBUG")
			|| ft_strequ(lvl, "info") || ft_strequ(lvl, "INFO")
			|| ft_strequ(lvl, "warn") || ft_strequ(lvl, "WARN")
			|| ft_strequ(lvl, "error") || ft_strequ(lvl, "ERROR"));
}

void		vm_options_logger(int ac, char **av)
{
	register int	i;

	i = 1;
	while (i < ac && !(ft_strequ(av[i], "-l") || ft_strequ(av[i], "-log")))
		i++;
	while (++i < ac)
		if (ft_strequ(av[i], "color"))
			logger_switch_flags(L_USE_COLORS, L_ENABLE);
		else if (ft_strequ(av[i], "prefix"))
			logger_switch_flags(L_SHOW_PREFIX | L_SHOW_TIME | L_SHOW_FUNC,
				L_ENABLE);
		else if (ft_strequ(av[i], "file"))
			if (i + 1 >= ac || is_log_level(av[i + 1]))
				logger_add_app("app", NULL, ALL);
			else
			{
				logger_switch_flags(L_FILE_SPEC, L_ENABLE);
				logger_add_app(av[i + 1], av[i + 1], ALL);
			}
		else if (is_log_level(av[i]))
		{
			logger_set_log_lvl(log_level(av[i]));
			return ;
		}
}
