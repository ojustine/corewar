#include "conv.h"
#include "str.h"
#include "mem.h"
#include "error.h"
#include "util.h"
#include "vm.h"

static int	vm_store_champion(t_champ *champ, t_champ **storage)
{
	static size_t	champ_counter;

	log_trace(__func__, "Store champion");
	if (champ_counter == MAX_PLAYERS)
	{
		log_error(__func__, "Number of champions exceeded maximum: %zu",
			MAX_PLAYERS);
		return (0);
	}
	if (champ->id > (int)g_vm.champ_size)
	{
		log_warn(__func__, "Id %d exceed number of champs %zu. Use undef.",
			champ->id, g_vm.champ_size);
		champ->id = -1;
	}
	if (champ->id != -1 && storage[champ->id] != NULL)
	{
		log_warn(__func__, "Id %d is already taken. Use undef.", champ->id);
		champ->id = -1;
	}
	storage[champ_counter++] = champ;
	return (1);
}

static void	vm_setup_champions_code(void)
{
	int			i;
	intptr_t	pc;

	log_trace(__func__, "Set champions on arena");
	i = 0;
	pc = 0;
	while (i < (int)g_vm.champ_size)
	{
		ft_memcpy(&g_vm.arena[pc], g_vm.champ[i]->code,
			g_vm.champ[i]->header.prog_size);
		log_debug(__func__, "Champion '%s' placed from %P to %P",
			g_vm.champ[i]->header.prog_name, pc,
			pc + g_vm.champ[i]->header.prog_size);
		pc += MEM_SIZE / g_vm.champ_size;
		i++;
	}
	g_vm.last_alive = (int)g_vm.champ_size;
}

void		vm_setup_champions_ids(t_champ **storage)
{
	register int	i;
	register int	j;

	log_trace(__func__, "Set champion ids");
	i = -1;
	while (++i < (int)g_vm.champ_size)
		if (storage[i]->id != -1)
			g_vm.champ[storage[i]->id - 1] = storage[i];
	i = -1;
	j = 0;
	while (++i < (int)g_vm.champ_size)
	{
		if (storage[i]->id == -1)
		{
			while (j < (int)g_vm.champ_size && g_vm.champ[j] != NULL)
				j++;
			storage[i]->id = j + 1;
			g_vm.champ[j] = storage[i];
		}
	}
	i = -1;
	while (++i < (int)g_vm.champ_size)
		log_debug(__func__, "Id %d: champion '%s'",
			g_vm.champ[i]->id, g_vm.champ[i]->header.prog_name);
}

t_champ		*vm_new_champion(const char *str_id, char *path)
{
	t_champ		*champ;
	long long	id;

	log_trace(__func__, "Allocate a new champion '%s'", path);
	champ = ft_memalloc(sizeof(t_champ));
	ft_assert(champ != NULL, __func__, E_ALLOC);
	if (str_id)
	{
		log_trace(__func__, "Resolve champion id");
		id = ft_atol(str_id);
		if (id < 1 || id > MAX_PLAYERS)
		{
			log_warn(__func__, "Invalid id's value: %lld. Use undef.", id);
			id = -1;
		}
		champ->id = (int)id;
	}
	else
		champ->id = -1;
	ft_at_exit_ptr(free, champ, "Freeing champion");
	log_debug(__func__, "Create a new champion '%s' with predefined id %d",
		path, champ->id);
	return (champ);
}

int			vm_load_champions(int ac, char **av)
{
	t_champ			*storage[MAX_PLAYERS];
	t_champ			*champ;
	char			*str_id;
	register int	i;

	ft_bzero(&storage, sizeof(storage));
	str_id = NULL;
	i = 0;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-n"))
			str_id = av[++i];
		else if (ft_strend(av[i], COR_EXT))
		{
			champ = vm_new_champion(str_id, av[i]);
			if (!vm_read_champion(champ, av[i])
			|| !vm_store_champion(champ, storage))
				return (0);
			str_id = NULL;
		}
	}
	vm_setup_champions_ids(storage);
	vm_setup_champions_code();
	log_debug(__func__, "Successfully load %zu champions", g_vm.champ_size);
	return (1);
}
