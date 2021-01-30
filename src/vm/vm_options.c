#include "conv.h"
#include "str.h"
#include "vm.h"

static int	vm_option_dump(t_vm *vm, int *i, int ac, char **av)
{
	log_trace(__func__, "Resolve option '-dump'");
	vm->config |= VM_DUMP;
	if (av[*i][1] == 's')
		vm->config |= VM_STEP;
	if (*i + 1 < ac && ft_isuint(av[*i + 1]))
	{
		(*i)++;
		vm->dump_cycles = (int)ft_atol(av[*i]);
		if (ft_isuint(av[*i + 1]))
		{
			(*i)++;
			vm->dump_byteness = (int)ft_atol(av[*i]);
		}
		else
			vm->dump_byteness = DUMP_BYTENESS;
		log_info(__func__,
				"Dump after '%d' turns, byteness '%d' octets per line",
				vm->dump_cycles, vm->dump_byteness);
		return (1);
	}
	log_error(__func__, "Incorrect use of the option '-dump'");
	return (0);
}

static int	vm_option_verbose(t_vm *vm, int *i, int ac, char **av)
{
	unsigned	verbose;

	log_trace(__func__, "Resolve option '-verbose'");
	if (*i + 1 < ac && ft_isuint(av[*i + 1]))
	{
		(*i)++;
		verbose = (unsigned)ft_atol(av[*i]);
		vm->config |= verbose & 0x1F;
		log_info(__func__, "Verbose levels: '%b'", verbose);
		return (1);
	}
	log_error(__func__, "Incorrect use of the option '-verbose'");
	return (0);
}

static int	vm_option_n(t_vm *vm, int *i, int ac, char **av)
{
	log_trace(__func__, "Resolve option '-n'");
	if (*i + 2 < ac
		&& ft_isuint(av[*i + 1])
		&& ft_strend(av[*i + 2], COR_EXT)
		&& ft_strlen(av[*i + 2]) > sizeof(COR_EXT))
	{
		log_debug(__func__, "Predefine id '%s' for champion '%s'",
			av[*i + 1], av[*i + 2]);
		vm->champ_size++;
		log_debug(__func__, "The count of champions is now '%zu'",
			vm->champ_size);
		*i += 2;
		return (1);
	}
	log_error(__func__, "Incorrect use of the option '-n'");
	return (0);
}

static int	vm_option_other(t_vm *vm, char *av)
{
	if (ft_strequ(av, "-a") || ft_strequ(av, "-aff"))
	{
		log_trace(__func__, "Resolve option '-aff'");
		vm->config |= VM_AFF;
		log_info(__func__, "Printing output from 'aff' is enabled");
	}
	else if (ft_strequ(av, "-c") || ft_strequ(av, "-color"))
	{
		log_trace(__func__, "Resolve option '-color'");
		vm->config |= VM_COLOR;
		log_info(__func__, "Colored output is enabled");
	}
	else if (ft_strend(av, COR_EXT) && ft_strlen(av) > sizeof(COR_EXT))
	{
		log_trace(__func__, "Resolve champion: '%s'", av);
		vm->champ_size++;
		log_debug(__func__, "The count of champions is now '%zu'",
			vm->champ_size);
	}
	else
	{
		log_error(__func__, "Unknown argument: '%s'", av);
		return (0);
	}
	return (1);
}

int			vm_options(t_vm *vm, int ac, char **av)
{
	int	ok;
	int	i;

	ok = 1;
	i = 0;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-d") || ft_strequ(av[i], "-s")
			|| ft_strequ(av[i], "-dump") || ft_strequ(av[i], "-step"))
			ok = vm_option_dump(vm, &i, ac, av);
		else if (ft_strequ(av[i], "-v") || ft_strequ(av[i], "-verbose"))
			ok = vm_option_verbose(vm, &i, ac, av);
		else if (ft_strequ(av[i], "-l") || ft_strequ(av[i], "-log"))
			;//vm_options_l(vm, &i, ac, av);
		else if (ft_strequ(av[i], "-n"))
			ok = vm_option_n(vm, &i, ac, av);
		else
			ok = vm_option_other(vm, av[i]);
		if (!ok)
		{
			return (0);//todo usage?
		}
	}
	return (1);
}
