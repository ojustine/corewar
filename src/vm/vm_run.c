#include "vm.h"

static void	vm_set_champions(t_vm *vm)
{
	int	i;
	int	pc;

	log_trace(__func__, "Set champions on arena");
	i = 0;
	pc = 0;
	while (i < (int)vm->champ_size)
	{
		ft_memcpy(&vm->arena[pc], vm->champ[i]->code,
			vm->champ[i]->header.prog_size);
		pc += MEM_SIZE / (int)vm->champ_size;
		log_debug(__func__, "Champion '%s' placed from '%#X' to '%#X'",
			vm->champ[i]->header.prog_name, pc, pc + (int)vm->champ_size);
		i++;
	}
	vm->last_alive = (int)vm->champ_size - 1;
}

void	vm_run(t_vm *vm)
{
	log_trace(__func__, "Run Corewar Virtual Machine");
	//todo print_intro
	vm_set_champions(vm);
	vm_cursor_set_initial(vm);
	while (vm->cursors->size)
	{
		if (vm->config & VM_DUMP && !(vm->cycles % vm->dump_cycles))
		{
			//todo vm_dump
			exit(0);
		}
		vm_exec(vm);
//		if (vm->cycles_to_die == vm->cycles_after_check
//			|| vm->cycles_to_die <= 0)
//			cycles_to_die_check(vm);
	}
}
