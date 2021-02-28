#include "ft_printf.h"
#include "vm.h"

void	verbose_cycle(void)
{
	ft_printf("It is now cycle %d\n", g_vm.cycles);
}

void	verbose_move_pc(intptr_t pc, intptr_t step)
{
	char			buf[SHOW_MEM_MAX * 3 + 1];

	vm_show_mem(pc, buf, step);
	ft_printf("ADV %d (%0.4p -> %0.4p) %s\n", step, pc, pc + step, buf);
}

void	verbose_cursor_death(t_cursor *cursor)
{
	ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
		cursor->id, g_vm.cycles - cursor->live_cycle, g_vm.cycles_to_die);
}

void	verbose_cycles_to_die(void)
{
	ft_printf("Cycle to die is now %zd\n", g_vm.cycles_to_die);
}
