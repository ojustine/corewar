#include "ft_printf.h"
#include "vm.h"

extern const char	g_arg_log[3][43];

inline static void	op_verbose(t_cursor *cursor, intptr_t arg, intptr_t addr)
{
	ft_printf("P %4d | fork %d (%lld)\n", cursor->id, arg, addr);
}

void				op_fork(t_cursor *cursor)
{
	const intptr_t	arg_0 = get_arg_value(cursor, 0, 1);
	const intptr_t	addr = arg_0 % IDX_MOD + cursor->pc;
	t_cursor		*new_cursor;

	new_cursor = vm_cursor_new(vm_trunc(addr));
	ft_memcpy(new_cursor->reg, cursor->reg, sizeof(int32_t) * (REG_NUMBER + 1));
	new_cursor->carry = cursor->carry;
	new_cursor->live_cycle = cursor->live_cycle;
	list_push_front(g_vm.cursors, new_cursor);
	log_debug(__func__, "Cursor %d: exec 'fork': %s -> cursor %d (%P)",
		cursor->id, g_arg_log[0], new_cursor->id, addr);
	if (g_vm.config & VM_VERBOSE_OP)
		op_verbose(cursor, arg_0, addr);
}
