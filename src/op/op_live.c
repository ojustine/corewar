#include "ft_printf.h"
#include "vm.h"

extern const char	g_arg_log[3][43];

inline static void	op_verbose(t_cursor *cursor, int player_id)
{
	ft_printf("P %4d | live %d\n", cursor->id, player_id);
}

inline static void	op_verbose_alive(int player_id, char *player_name)
{
	ft_printf("Player %d (%s) is said to be alive\n", player_id, player_name);
}

void				op_live(t_cursor *cursor)
{
	const int	arg_0 = get_arg_value(cursor, 0, 0);
	const int	id = -arg_0;

	g_vm.lives_nbr++;
	cursor->live_nbr++;
	cursor->live_cycle = g_vm.cycles;
	if (id >= 1 && id <= (int)g_vm.champ_size)
	{
		g_vm.last_alive = id;
		log_debug(__func__, "Cursor %d: exec 'live': %s -> %d ('%s') is alive",
			cursor->id, g_arg_log[0], id,
			(char *)g_vm.champ[id - 1]->header.prog_name);
		if (g_vm.config & VM_VERBOSE_LIVE)
			op_verbose_alive(id, (char *)g_vm.champ[id - 1]->header.prog_name);

	}
	if (g_vm.config & VM_VERBOSE_OP)
		op_verbose(cursor, arg_0);
}
