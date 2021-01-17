#include "conv.h"
#include "str.h"
#include "vm.h"

static int	vm_options_dump(t_vm *vm, int ac, char **av)
{
	int	byteness;

	if (ac < 2 || !ft_isint(*(av + 1)))
	{
		log_warn(__func__, "Dump without number of cycles. Use default: '%d'",
							DEFAULT_DUMP_CYCLES);
	}
	else
	{
		byteness = 0;
	}
	if (ft_strnequ(*av, "-s", 2) || ft_strnequ(*av, "-step", 5))
		vm->flags |= VM_AFF;
	while (**av >= 'a' && **av < 'z')
		(*av)++;
	byteness = (int)ft_atol(*av);
	if (byteness <= 0)
	{
		log_info(__func__, "Dump without byteness. Use default: '%d'",
							DEFAULT_DUMP_BYTENESS);

	}
}

int			vm_options(t_vm *vm, int ac, char **av)
{
	int	i;

	i = 1;
	while (ac-- > 1)
	{
		if (ft_strequ(av[i], "-a") || ft_strequ(av[i], "-aff"))
			vm->flags |= VM_AFF;
		else if (ft_strnequ(av[i], "-d", 2) || ft_strnequ(av[i], "-s", 2)
		|| ft_strnequ(av[i], "-dump", 5) || ft_strnequ(av[i], "-step", 5))
			vm_options_dump(vm, ac, av);

	}
}
