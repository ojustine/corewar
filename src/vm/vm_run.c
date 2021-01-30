#include "vm.h"

void	vm_set_champions(t_vm *vm)
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

void	vm_eval(t_vm *vm, t_cursor *cursor)
{
	if (cursor->cycles_to_exec > 0)
		cursor->cycles_to_exec--;
	else
	{
		//update_op_code(vm, cursor);
		op = NULL;
		if (cursor->op_code >= 0x01 && cursor->op_code <= 0x10)
			op = &g_op[INDEX(cursor->op_code)];
		if (op)
		{
			parse_types_code(vm, cursor, op);
			if (is_arg_types_valid(cursor, op) && is_args_valid(cursor, vm, op))
				op->func(vm, cursor);
			else
				cursor->step += calc_step(cursor, op);
			if (vm->log & PC_MOVEMENT_LOG && cursor->step)
				log_pc_movements(vm->arena, cursor);
		}
		else
			cursor->step = OP_CODE_LEN;
		move_cursor(vm, cursor);
	}
}

void	vm_exec(t_vm *vm)
{
	register t_list_node	*node;

	node = vm->cursors->front;
	vm->cycles++;
	vm->cycles_after_check++;
	if (vm->config & VM_VERBOSE_CYCLE)
		;////todo log cycle
	while (node)
	{
		vm_eval(vm, (t_cursor *)node->data);
		node = node->next;
	}
}

void	vm_run(t_vm *vm)
{
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
