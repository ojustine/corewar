#include "util.h"
#include "error.h"
#include "vm.h"

t_cursor	*vm_cursor_new(intptr_t pc)
{
	t_cursor	*cursor;
	static int	cursor_id;

	cursor = ft_memalloc(sizeof(t_cursor));
	ft_assert(cursor != NULL, __func__, E_ALLOC);
	cursor->id = ++cursor_id;
	cursor->pc = pc;
	log_debug(__func__, "Cursor %d: created with pc: %P", cursor->id,
		cursor->pc);
	return (cursor);
}

void		vm_cursor_move(t_cursor *cursor)
{
	char			buf[SHOW_MEM_MAX * 3 + 1];
	const intptr_t	old_pc = cursor->pc;
	const intptr_t	step = cursor->step;

	if (step == 0)
		return ;
	cursor->pc += step;
	cursor->step = 0;
	if (cursor->pc >= MEM_SIZE)
		cursor->pc %= MEM_SIZE;
	log_trace(__func__, "Cursor '%d': move PC by '%zu' bytes (%P >>> %P) %s",
		cursor->id, step, old_pc, cursor->pc, vm_show_mem(old_pc, buf, step));
	if (g_vm.config & VM_VERBOSE_MOVE)
		verbose_move_pc(old_pc, step);
}

void		vm_cursor_set_initial(void)
{
	t_cursor	*cursor;
	int			i;
	intptr_t	pc;

	log_trace(__func__, "Set initial cursors");
	i = 0;
	pc = 0;
	g_vm.cursors = list_new();
	ft_assert(g_vm.cursors != NULL, __func__, E_ALLOC);
	while (i < (int)g_vm.champ_size)
	{
		cursor = vm_cursor_new(pc);
		cursor->reg[1] = -g_vm.champ[i]->id;
		cursor->parent = g_vm.champ[i];
		list_push_front(g_vm.cursors, cursor);
		pc += MEM_SIZE / (int)g_vm.champ_size;
		i++;
	}
	log_debug(__func__, "'%d' cursors set", i);
}
