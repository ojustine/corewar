#include "ft_printf.h"
#include "vm.h"

extern const char	g_arg_log[3][43];

void				op_aff(t_cursor *cursor)
{
	const int32_t	arg_0 = get_arg_value(cursor, 0, 0);

	if (g_vm.config & VM_AFF)
		ft_printf("Aff: %c\n", (char)arg_0);
	log_debug(__func__, "Cursor %d: exec 'aff': %s -> %c",
		cursor->id, g_arg_log[0], arg_0);
}
