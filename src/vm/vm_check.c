#include "ft_printf.h"
#include "vm.h"

static inline int	is_alive(t_cursor *cursor)
{
	const int alive = g_vm.cycles - cursor->live_cycle < g_vm.cycles_to_die;

	return (g_vm.cycles_to_die > 0 && alive);
}

static void			purge_dead_cursors(void)
{
	register size_t			i;
	register t_list_node	*node;
	t_list					*cursors;
	t_cursor				*cursor;

	cursors = g_vm.cursors;
	i = 0;
	node = cursors->front;
	while (i < cursors->size)
	{
		cursor = (t_cursor *)node->data;
		node = node->next;
		if (is_alive(cursor))
			i++;
		else
		{
			log_debug(__func__, "Cursor %d: is died after %d cycles",
				cursor->id, g_vm.cycles - cursor->live_cycle);
			if (g_vm.config & VM_VERBOSE_DEATH)
				verbose_cursor_death(cursor);
			list_pop(cursors, i);
			free(cursor);
		}
	}
}

void			vm_check(void)
{
	g_vm.checks_nbr++;
	log_trace(__func__, "Do check on cycle %d, checks number is now %d",
		g_vm.cycles, g_vm.checks_nbr);
	purge_dead_cursors();
	if (g_vm.checks_nbr == MAX_CHECKS || g_vm.lives_nbr >= NBR_LIVE)
	{
		g_vm.cycles_to_die -= CYCLE_DELTA;
		log_debug(__func__, "Cycles to die is now %d\n", g_vm.cycles_to_die);
		if (g_vm.config & VM_VERBOSE_CYCLE)
			verbose_cycles_to_die();
		g_vm.checks_nbr = 0;
	}
	g_vm.lives_nbr = 0;
	g_vm.cycles_after_check = 0;
}
