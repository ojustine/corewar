#include "ft_printf.h"
#include "vm.h"

void	vm_exec(void)
{
	register t_list_node	*node;

	g_vm.cycles++;
	g_vm.cycles_after_check++;
	log_debug(__func__, "Exec cycle %d", g_vm.cycles);
	if (g_vm.config & VM_VERBOSE_CYCLE)
		verbose_cycle();
	node = g_vm.cursors->front;
	while (node)
	{
		vm_eval((t_cursor *)node->data);
		node = node->next;
	}
}
