#include "ft_printf.h"
#include "vm.h"

extern const char	g_arg_log[3][43];

inline static void	op_verbose(t_cursor *cursor, int32_t value, int32_t reg)
{
	ft_printf("P %4d | ld %d r%d\n", cursor->id, value, reg);
}

void				op_ld(t_cursor *cursor)
{
	const int32_t	arg_0 = get_arg_value(cursor, 0, 1);
	const int32_t	reg_id_1 = cursor->args[1];

	cursor->carry = !arg_0;
	cursor->reg[reg_id_1] = arg_0;
	log_debug(__func__, "Cursor %d: exec 'ld': %s -> r%d",
		cursor->id, g_arg_log[0], reg_id_1);
	if (g_vm.config & VM_VERBOSE_OP)
		op_verbose(cursor, arg_0, reg_id_1);
}
