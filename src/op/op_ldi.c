#include "ft_printf.h"
#include "vm.h"

extern const char	g_arg_log[3][43];

inline static void	op_verbose(t_cursor *cursor, int32_t arg_0, int32_t arg_1,
					intptr_t addr)
{
	ft_printf("P %4d | ldi %d %d r%d\n", cursor->id, arg_0, arg_1,
		cursor->args[2]);
	ft_printf("       | -> load from %d + %d = %d (with pc and mod %lld)\n",
		arg_0, arg_1, arg_0 + arg_1, addr);
}

void				op_ldi(t_cursor *cursor)
{
	const int32_t	arg_0 = get_arg_value(cursor, 0, 1);
	const int32_t	arg_1 = get_arg_value(cursor, 1, 1);
	const int32_t	reg_2_id = cursor->args[2];
	int32_t			value;
	intptr_t		addr;

	addr = vm_trunc(cursor->pc + (arg_0 + arg_1) % IDX_MOD);
	value = vm_load_mem(addr, REG_SIZE);
	cursor->reg[reg_2_id] = value;
	log_debug(__func__, "Cursor %d: exec 'ldi': %s + %s = %d (%P) -> r%d",
		cursor->id, g_arg_log[0], g_arg_log[1], value, addr, reg_2_id);
	if (g_vm.config & VM_VERBOSE_OP)
		op_verbose(cursor, arg_0, arg_1, value);
}
