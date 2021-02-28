#include "io_.h"
#include "str.h"
#include "conv.h"
#include "util.h"
#include "vm.h"

void	vm_dump(void)
{
	char *user_input;

	print_arena();
	if (g_vm.config & VM_STEP_DUMP)
	{
		if (get_next_line(0, &user_input) == -1)
			ft_exit(EXIT_FAILURE, "Reading from STDIN is failed");
		log_info(__func__, "User input: %s", user_input);
		if (ft_isuint(user_input))
			g_vm.dump_cycle += (int)ft_atol(user_input);
		else
			g_vm.dump_cycle += g_vm.dump_cycle;
		return ;
	}
	ft_exit(EXIT_SUCCESS, "Stop Corewar Virtual Machine after dump");
}

void	vm_run(void)
{
	log_info(__func__, "Run Corewar Virtual Machine");
	vm_cursor_set_initial();
	print_intro();
	while (g_vm.cursors->size)
	{
		if (g_vm.config & VM_DUMP && g_vm.dump_cycle == g_vm.cycles)
			vm_dump();
		vm_exec();
		if (g_vm.cycles_to_die == g_vm.cycles_after_check
			|| g_vm.cycles_to_die <= 0)
			vm_check();
	}
	print_winner();
}

int		main(int ac, char **av)
{
	ft_bzero(&g_vm, sizeof(t_vm));

	logger_set_app_log_lvl(L_STDOUT, OFF);
	logger_switch_flags(L_USE_COLORS, L_ENABLE);
	if (!vm_options(ac, av))
		ft_exit(EXIT_FAILURE, "Resolving arguments failed");
	if (!vm_load_champions(ac, av))
		ft_exit(EXIT_FAILURE, "Loading champions failed");
	g_vm.cycles_to_die = CYCLE_TO_DIE;
	vm_run();
	//ft_exit(0, NULL);
}
