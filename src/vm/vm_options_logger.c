//#include "conv.h"
//#include "str.h"
//#include "vm.h"
//
//int	vm_options_logger(int *i, int ac, char **av)
//{
//	int	ok;
//
//	ok = 1;
//	i = 0;
//	while (++i < ac)
//	{
//		if (ft_strequ(av[i], "-d") || ft_strequ(av[i], "-s")
//			|| ft_strequ(av[i], "-dump") || ft_strequ(av[i], "-step"))
//			ok = vm_option_dump(&i, ac, av);
//		else if (ft_strequ(av[i], "-v") || ft_strequ(av[i], "-verbose"))
//			ok = vm_option_verbose(&i, ac, av);
//		else if (ft_strequ(av[i], "-n") || ft_strequ(av[i], "-number"))
//			ok = vm_option_n(&i, ac, av);
//		else if (ft_strequ(av[i], "-l") || ft_strequ(av[i], "-log"))
//			;//vm_options_l(&i, ac, av);
//		else
//			ok = vm_option_other(av[i]);
//		if (!ok)
//		{
//			return (0);//todo usage?
//		}
//	}
//	log_debug(__func__, "The number of champions is '%zu'", g_vm.champ_size);
//	return (1);
//}
