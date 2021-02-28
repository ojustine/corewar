#include "conv.h"
#include "str.h"
#include "vm.h"

static int	vm_option_dump(int *i, int ac, char **av)
{
	g_vm.config |= VM_DUMP;
	if (av[*i][1] == 's')
	{
		g_vm.config |= VM_STEP_DUMP;
		log_trace(__func__, "Resolve option 'step'");
	}
	else
		log_trace(__func__, "Resolve option 'dump'");
	if (*i + 1 < ac && ft_isuint(av[*i + 1]))
	{
		(*i)++;
		g_vm.dump_cycle = (int)ft_atol(av[*i]);
		if (*i + 1 < ac && ft_isuint(av[*i + 1]))
		{
			(*i)++;
			g_vm.dump_byteness = (int)ft_atol(av[*i]);
		}
		else
			g_vm.dump_byteness = DUMP_BYTENESS;
		log_info(__func__, "Dump after %d cycles, %d octets per line",
			g_vm.dump_cycle, g_vm.dump_byteness);
		return (1);
	}
	log_error(__func__, "Incorrect use of the option 'dump' or 'step'");
	return (0);
}

static int	vm_option_verbose(int *i, int ac, char **av)
{
	unsigned	verbose;

	log_trace(__func__, "Resolve option 'verbose'");
	if (*i + 1 < ac && ft_isuint(av[*i + 1]))
	{
		(*i)++;
		verbose = (unsigned)ft_atol(av[*i]);
		g_vm.config |= verbose & 0x1F;
		log_info(__func__, "Verbose levels: %08b", verbose);
		return (1);
	}
	log_error(__func__, "Incorrect use of the option 'verbose'");
	return (0);
}

static int	vm_option_n(int *i, int ac, char **av)
{
	log_trace(__func__, "Resolve option 'number'");
	if (*i + 2 < ac
		&& ft_isuint(av[*i + 1])
		&& ft_strend(av[*i + 2], COR_EXT)
		&& ft_strlen(av[*i + 2]) > sizeof(COR_EXT))
	{
		log_debug(__func__, "Resolve champion: '%s' with predefined id %s",
			av[*i + 2], av[*i + 1]);
		g_vm.champ_size++;
		*i += 2;
		return (1);
	}
	log_error(__func__, "Incorrect use of the option 'number'");
	return (0);
}

static int	vm_option_other(char *av)
{
	if (ft_strequ(av, "-a") || ft_strequ(av, "-aff"))
	{
		log_trace(__func__, "Resolve option 'aff'");
		g_vm.config |= VM_AFF;
		log_info(__func__, "Printing output from 'aff' is enabled");
	}
	else if (ft_strequ(av, "-c") || ft_strequ(av, "-color"))
	{
		log_trace(__func__, "Resolve option 'color'");
		g_vm.config |= VM_COLOR;
		log_info(__func__, "Colored output is enabled");
	}
	else if (ft_strend(av, COR_EXT) && ft_strlen(av) > sizeof(COR_EXT))
	{
		log_trace(__func__, "Resolve champion: '%s'", av);
		g_vm.champ_size++;
	}
	else
	{
		log_error(__func__, "Unknown option: '%s'", av);
		return (0);
	}
	return (1);
}

int			vm_options(int ac, char **av)
{
	int	ok;
	int	i;

	ok = 1;
	i = 0;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-d") || ft_strequ(av[i], "-s")
			|| ft_strequ(av[i], "-dump") || ft_strequ(av[i], "-step"))
			ok = vm_option_dump(&i, ac, av);
		else if (ft_strequ(av[i], "-v") || ft_strequ(av[i], "-verbose"))
			ok = vm_option_verbose(&i, ac, av);
		else if (ft_strequ(av[i], "-n") || ft_strequ(av[i], "-number"))
			ok = vm_option_n(&i, ac, av);
		else if (ft_strequ(av[i], "-l") || ft_strequ(av[i], "-log"))
			;//vm_options_l(&i, ac, av);
		else
			ok = vm_option_other(av[i]);
		if (!ok)
		{
			return (0);//todo usage?
		}
	}
	log_debug(__func__, "The number of champions is '%zu'", g_vm.champ_size);
	return (1);
}
