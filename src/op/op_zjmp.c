#include "ft_printf.h"
#include "vm.h"

extern const char	g_arg_log[3][43];

inline static void	op_verbose(t_cursor *cursor, int32_t addr)
{
	ft_printf("P %4d | zjmp %d %s\n", cursor->id, addr,
		cursor->carry ? "OK" : "FAILED");
}

void				op_zjmp(t_cursor *cursor)
{
	const int32_t	arg_0 = get_arg_value(cursor, 0, 0);
	const intptr_t	addr = vm_trunc(cursor->pc + arg_0 % IDX_MOD);

	log_debug(__func__, "Cursor %d: exec 'zjmp': %s (%P >>> %P) %s",
		cursor->id, g_arg_log[0], cursor->pc, addr,
		cursor->carry ? "OK" : "FAILED");
	if (cursor->carry)
	{
		cursor->pc = addr;
		cursor->step = 0;
	}
	if (g_vm.config & VM_VERBOSE_OP)
		op_verbose(cursor, arg_0);
}
