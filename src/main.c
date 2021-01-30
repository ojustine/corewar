#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <hash_map.h>
#include <mem.h>
#include <util.h>
#include <str.h>
#include <list.h>
#include <ft_printf.h>
#include <time.h>
#include "system.h"
#include "vm.h"
#include "ft_regex.h"



int main(/*int ac, char **av*/)
{
	t_vm	*vm;

	logger_set_app_log_lvl(L_STDOUT, TRACE);
	logger_switch_flags(L_USE_COLORS, L_ENABLE);
	char *s[] = {"", "-n", "2", "/Users/ojustine/Desktop/corewar/bee_gees.cor", "/Users/ojustine/Desktop/corewar/zork.cor", "-c"};
	//char *s[] = {"", "C:\\Users\\Ojustine\\Desktop\\corewar\\bee_gees.cor", "C:\\Users\\Ojustine\\Desktop\\corewar\\bee_gees.cor", "C:\\Users\\Ojustine\\Desktop\\corewar\\bee_gees.cor", "C:\\Users\\Ojustine\\Desktop\\corewar\\zork.cor", "C:\\Users\\Ojustine\\Desktop\\corewar\\bee_gees.cor"};

	vm = ft_memalloc(sizeof(t_vm));
	ft_at_exit_ptr(free, vm, "Freeing VM");

	if (!vm_options(vm, 6, s))
		ft_exit(EXIT_FAILURE, "Resolving arguments failed");
	if (!vm_load_champions(vm, 6, s))
		ft_exit(EXIT_FAILURE, "Loading champions failed");
	vm_run(vm);
	ft_exit(0, NULL);

//	clock_t begin = clock();
//
////	char *s;
////	t_list *l = list_new();
////	for (int i = 0; i < 1000000; i++)
////	{
////		list_push_back(l, "m");
////	}
////	s = malloc(1000001);
////	int i = 0;
////	for (; i < 1000000; i++)
////	{
////		s[i] = *((char*)list_pop_front(l));
////	}
////	s[i] = '\0';
////	ft_printf(s);
//
//	for (int i = 0; i < 1000000; i++)
//		write(1, "\bm", 2);
//
//	clock_t end = clock();
//	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
//	printf("\n%lf", time_spent);
}
