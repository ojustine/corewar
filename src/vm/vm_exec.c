#include "vm.h"

void	vm_exec(t_vm *vm)
{
	register t_list_node	*node;

	node = vm->cursors->front;
	vm->cycles++;
	vm->cycles_after_check++;
	log_debug(__func__, "Exec cycle '%d'", vm->cycles);
	if (vm->config & VM_VERBOSE_CYCLE)
		;////todo log cycle
	while (node)
	{
		vm_eval(vm, (t_cursor *)node->data);
		node = node->next;
	}
}
