#include "ft_printf.h"
#include "vm.h"

extern const char	g_arg_log[3][43];

inline static void	op_verbose(t_cursor *cursor, int32_t reg_2)
{
	ft_printf("P %4d | add r%d r%d r%d\n", cursor->id, cursor->args[0],
		cursor->args[1], reg_2);
}

void				op_add(t_cursor *cursor)
{
	const int32_t	arg_0 = get_arg_value(cursor, 0, 0);
	const int32_t	arg_1 = get_arg_value(cursor, 1, 0);
	const int32_t	reg_2_id = cursor->args[2];
	int32_t			value;

	value = arg_0 + arg_1;
	cursor->carry = !value;
	cursor->reg[reg_2_id] = value;
	log_debug(__func__, "Cursor %d: exec 'add': %s + %s = %d -> r%d",
		cursor->id, g_arg_log[0], g_arg_log[1], value, reg_2_id);
	if (g_vm.config & VM_VERBOSE_OP)
		op_verbose(cursor, reg_2_id);
}
