#include "vm.h"

static void	set_arg_type(int8_t arg_type, int8_t index, t_cursor *cursor)
{
	cursor->args_types[index - 1] = g_arg_code[INDEX(arg_type)];
}

int32_t		calc_addr(int32_t addr)
{
	addr %= MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	return (addr);
}

inline int8_t	get_byte(t_vm *vm, int32_t pc, int32_t step)
{
	return (vm->arena[calc_addr(pc + step)]);
}

void		parse_types_code(t_vm *vm, t_cursor *cursor, t_op *op)
{
	int8_t args_types_code;

	if (op->args_types_code)
	{
		args_types_code = get_byte(vm, cursor->pc, 1);
		if (op->args_num >= 1)
			set_arg_type((int8_t)((args_types_code & 0xC0) >> 6), 1, cursor);
		if (op->args_num >= 2)
			set_arg_type((int8_t)((args_types_code & 0x30) >> 4), 2, cursor);
		if (op->args_num >= 3)
			set_arg_type((int8_t)((args_types_code & 0xC) >> 2), 3, cursor);
	}
	else
		cursor->args_types[0] = op->args_types[0];
}

static void	vm_eval_opcode(t_vm *vm, t_cursor *cursor)
{
	log_trace(__func__, "Cursor: '%d', eval opcode", cursor->id);
	cursor->op_code = vm->arena[cursor->pc];
	if (cursor->op_code > 0x10)
		cursor->op_code = 0;
	cursor->cycles_to_exec = g_op[cursor->op_code].cycles;
	log_debug(__func__, "Cursor: '%d', opcode: '%x', cycles to exec: '%d'",
		cursor->id, cursor->op_code, cursor->cycles_to_exec);
}

void	vm_eval(t_vm *vm, t_cursor *cursor)
{
	log_trace(__func__, "Cursor: '%d', eval cycle", cursor->id);
	if (cursor->cycles_to_exec == 0)
		vm_eval_opcode(vm, cursor);
	if (cursor->cycles_to_exec > 0)//todo log
		cursor->cycles_to_exec--;
	if (cursor->cycles_to_exec == 0)
	{
		t_op *op = NULL;
		if (cursor->op_code)
		{
			op = &g_op[cursor->op_code];
			parse_types_code(vm, cursor, op);
			if (is_arg_types_valid(cursor, op) && is_args_valid(cursor, vm, op))
				op->func(vm, cursor);
			else
				cursor->step += calc_step(cursor, op);
			if (vm->config & VM_VERBOSE_MOVE && cursor->step)
				;//log_pc_movements(vm->arena, cursor);todo
		}
		else
			cursor->step = OP_CODE_LEN;
		move_cursor(vm, cursor);
	}
}
