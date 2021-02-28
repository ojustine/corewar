#include "ft_printf.h"
#include "util.h"
#include "vm.h"

void	vm_run(void)
{
	int	dump_exit;

	log_info(__func__, "Run Corewar Virtual Machine");
	vm_cursor_set_initial();
	print_intro();
	dump_exit = 0;
	while (g_vm.cursors->size)
	{
		if (g_vm.config & VM_DUMP && g_vm.dump_cycle == g_vm.cycles)//!(g_vm.cycles % g_vm.dump_cycle))todo step
		{
			dump_exit = 1;
			print_arena();
			break ;
		}
		vm_exec();
		if (g_vm.cycles_to_die == g_vm.cycles_after_check
			|| g_vm.cycles_to_die <= 0)
			vm_check();
	}
	if (!dump_exit)
		print_winner();
}

int		main(int ac, char **av)
{
	ft_bzero(&g_vm, sizeof(t_vm));

	logger_set_app_log_lvl(L_STDOUT, DEBUG);
	logger_switch_flags(L_USE_COLORS, L_ENABLE);
	if (!vm_options(ac, av))
		ft_exit(EXIT_FAILURE, "Resolving arguments failed");
	if (!vm_load_champions(ac, av))
		ft_exit(EXIT_FAILURE, "Loading champions failed");
	g_vm.cycles_to_die = CYCLE_TO_DIE;
	vm_run();
	//ft_exit(0, NULL);
}
