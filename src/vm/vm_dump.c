#include "str.h"
#include "io_.h"
#include "vm.h"

void	vm_dump(void)
{
	char *user_input;

	print_arena();
	if (g_vm.config & VM_STEP_DUMP)
	{
		get_next_line(0, &user_input);
		log_info("User input: %s", user_input);
		if (ft_isuint(user_input))
		{

		}
	}
}
