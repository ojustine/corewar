#include "math.h"
#include "ft_printf.h"
#include "vm.h"

inline static void	op_verbose(t_cursor *cursor, int32_t reg, int32_t addr)
{
	ft_printf("P %4d | st r%d %d\n", cursor->id, reg, addr);
}

void				op_st(t_cursor *cursor)
{
	const int32_t	reg_0_id = cursor->args[0];
	int32_t			value;
	int32_t			addr;

	value = cursor->reg[reg_0_id];
	if (cursor->args_types[1] == T_REG)
	{
		addr = cursor->args[1];
		cursor->reg[addr] = cursor->reg[reg_0_id];
		log_debug(__func__, "Cursor %d: exec 'st': r%d (%d) -> r%d",
			cursor->id, reg_0_id, value, addr);
	}
	else
	{
		addr = cursor->args[1] % IDX_MOD;
		vm_store_mem(value, addr + cursor->pc, REG_SIZE);
		vm_mark_mem(cursor->mark, addr + cursor->pc, REG_SIZE);
		log_debug(__func__, "Cursor %d: exec 'st': r%d (%d) -> %P",
			cursor->id, reg_0_id, value, vm_trunc(addr + cursor->pc));
	}
	if (g_vm.config & VM_VERBOSE_OP)
		op_verbose(cursor, reg_0_id, addr);
}
