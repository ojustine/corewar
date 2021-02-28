#include "ft_printf.h"
#include "vm.h"

void		print_intro(void)
{
	int i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < (int)g_vm.champ_size)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			g_vm.champ[i]->id,
			g_vm.champ[i]->header.prog_size,
			g_vm.champ[i]->header.prog_name,
			g_vm.champ[i]->header.comment);
		i++;
	}
}

void		print_winner(void)
{
	ft_printf("Contestant %d, \"%s\", has won !\n",
		g_vm.last_alive,
		g_vm.champ[g_vm.last_alive - 1]->header.prog_name);
}

void		print_arena(void)
{
	const t_byte	*arena = g_vm.arena;//todo strbuilder
	register int	i;
	register int	j;

	i = 0;
	ft_printf("0x");
	while (i < MEM_SIZE)
	{
		ft_printf("%#04.4x : ", i);
		j = 0;
		while (j < g_vm.dump_byteness && j + i < MEM_SIZE)
		{
			ft_printf("%.2x ", arena[i + j]);
			j++;
		}
		ft_printf("\n");
		i += g_vm.dump_byteness;
	}
}
