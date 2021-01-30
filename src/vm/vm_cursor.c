#include <util.h>
#include <error.h>
#include "vm.h"

t_cursor	*vm_cursor_new(t_champ *parent, int pc)
{
	t_cursor	*cursor;
	static int	cursor_id;

	log_trace(__func__, "Allocate a new cursor");
	cursor = ft_memalloc(sizeof(t_cursor));
	ft_assert(cursor != NULL, __func__, E_ALLOC);
	cursor->id = ++cursor_id;
	cursor->pc = pc;
	cursor->reg[1] = -parent->id;
	cursor->parent = parent;
	log_debug(__func__, "Create a new cursor: id: '%d', pc: '%d', forked: '%s'",
		cursor->id, cursor->pc, cursor->parent->header.prog_name);
	return (cursor);
}

void		vm_cursor_set_initial(t_vm *vm)
{
	t_cursor	*cursor;
	int			i;
	int			pc;

	log_trace(__func__, "Set initial cursors");
	i = 0;
	pc = 0;
	vm->cursors = list_new();
	ft_assert(vm->cursors != NULL, __func__, E_ALLOC);
	while (i < (int)vm->champ_size)//todo начинает выполнять с какого айди?
	{
		cursor = vm_cursor_new(vm->champ[i], pc);
		list_push_front(vm->cursors, cursor);
		pc += MEM_SIZE / (int)vm->champ_size;
		i++;
	}
	log_debug(__func__, "'%d' cursors set", i);
}
