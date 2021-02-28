#include "ft_printf.h"
#include "vm.h"

extern const char	g_arg_log[3][43];

inline static void	op_verbose(t_cursor *cursor, int32_t arg_1, int32_t arg_2,
					intptr_t addr)
{
	ft_printf("P %4d | sti r%d %d %d\n", cursor->id, cursor->args[0], arg_1,
		arg_2);
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %lld)\n",
		arg_1, arg_2, arg_1 + arg_2, addr);
}

void				op_sti(t_cursor *cursor)
{
	const int32_t	arg_0 = get_arg_value(cursor, 0, 0);
	const int32_t	arg_1 = get_arg_value(cursor, 1, 1);
	const int32_t	arg_2 = get_arg_value(cursor, 2, 1);
	int32_t			res;
	intptr_t		addr;

	res = arg_1 + arg_2;
	addr = vm_trunc(cursor->pc + res % IDX_MOD);
	vm_store_mem(arg_0, addr, REG_SIZE);
	vm_mark_mem(cursor->mark, addr, REG_SIZE);
	log_debug(__func__, "Cursor %d: exec 'sti': %s -> %s + %s = %d (%P)",
		cursor->id, g_arg_log[0], g_arg_log[1], g_arg_log[2], res, addr);
	if (g_vm.config & VM_VERBOSE_OP)
		op_verbose(cursor, arg_1, arg_2, addr);
}
