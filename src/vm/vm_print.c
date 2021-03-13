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
	const t_byte	*arena = g_vm.arena;//todo strbuilder, color
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

void		print_usage(void)
{
	ft_printf("Usage: ./corewar [-a] [(-dump|-d) <num> [<num>]] [(-step|-s) "
		"<num> [<num>]] [(-verbose|-v) <num>] [(-log|-l) [color prefix] "
		"[(-file|-f) <path>] <LOG_LEVEL>] [-n <num>] <champion.cor> <...>\n");
	ft_printf("    -aff|-a            : Print output from \"aff\" "
		"(Default is off)\n");
	ft_printf("    -dump|-d <n> [<b>] : Dump memory after <num> cycles (<b> "
		"octets per line, default is %d) and exit\n", DUMP_BYTENESS);
	ft_printf("    -step|-s <n> [<b>] : Run <n> cycles, dump memory (<b> octets"
		" per line, default is %d), pause and repeat\n                         "
		"If input is a number, then next dump occurs after the entered number "
		"of cycles\n", DUMP_BYTENESS);
	ft_printf("    -n <n>             : Set <num> of the next player\n");
	ft_printf("    -verbose|-v <n>    : Verbose output levels:\n"
		"                           1  : Show lives\n"
		"                           2  : Show cycles\n"
		"                           4  : Show operations\n"
		"                           8  : Show deaths\n"
		"                           16 : Show PC movements\n");
	ft_printf("    -log|-l [...] <L>  : Logger levels and features:\n");
	ft_printf("                           <L>           : TRACE DEBUG INFO WARN"
		" ERROR\n");
	ft_printf("                           color         : colored output\n"
		"                           prefix        : information prefix before "
		"each message\n                           file [<path>] : information "
		"prefix before each message\n");
}
