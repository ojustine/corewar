#include "ft_printf.h"
#include "vm.h"

char	g_arg_log[3][43];

int32_t	get_arg_value(t_cursor *cursor, int index, int is_mod)
{
	intptr_t	addr;
	int32_t		value;
	int32_t		reg;

	if (cursor->args_types[index] == T_REG)
	{
		reg = cursor->args[index];
		value = cursor->reg[reg];
		ft_sprintf(g_arg_log[index], "r%d (%d)", reg, value);
	}
	else if (cursor->args_types[index] == T_IND)
	{
		addr = is_mod ? cursor->args[index] % IDX_MOD : cursor->args[index];
		addr = vm_trunc(cursor->args_pc[index] + addr);
		value = vm_load_mem(addr, REG_SIZE);
		ft_sprintf(g_arg_log[index], "%d (%P)", value, addr);
	}
	else
	{
		value = cursor->args[index];
		ft_sprintf(g_arg_log[index], "%d", value);
	}
	return (value);
}
