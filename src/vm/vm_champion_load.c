#include "conv.h"
#include "str.h"
#include "mem.h"
#include "error.h"
#include "util.h"
#include "vm.h"

int			vm_store_champ(t_vm *vm, t_champ *champ, t_champ *storage[])
{
	static size_t	champ_counter;

	log_debug(__func__, "Store champion");
	if (champ_counter == MAX_PLAYERS)
	{
		log_error(__func__, "Number of champions exceeded maximum: '%zu'",
			MAX_PLAYERS);
		return (0);
	}
	if (champ->id > (int)vm->champ_size)
	{
		log_warn(__func__, "Id '%d' exceed number of champs '%zu'. Use undef.",
			champ->id, vm->champ_size);
		champ->id = -1;
	}
	if (champ->id != -1 && storage[champ->id] != NULL)
	{
		log_warn(__func__, "Id '%d' is already taken. Use undef.", champ->id);
		champ->id = -1;
	}
	storage[champ_counter++] = champ;
	return (1);
}

void		vm_setup_champ_ids(t_vm *vm, t_champ **storage)
{
	register int	i;
	register int	j;

	log_trace(__func__, "Set champion ids");
	i = -1;
	while (++i < (int)vm->champ_size)
		if (storage[i]->id != -1)
			vm->champ[storage[i]->id - 1] = storage[i];
	i = -1;
	j = 0;
	while (++i < (int)vm->champ_size)
	{
		if (storage[i]->id == -1)
		{
			while (j < (int)vm->champ_size && vm->champ[j] != NULL)
				j++;
			storage[i]->id = j + 1;
			vm->champ[j] = storage[i];
		}
	}
	i = -1;
	while (++i < (int)vm->champ_size)
		log_debug(__func__, "Id '%d': champion '%s'",
			vm->champ[i]->id, vm->champ[i]->header.prog_name);
}

t_champ		*vm_new_champ(const char *str_id, char *path)
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
			log_warn(__func__, "Invalid id's value: '%lld'. Use undef.", id);
			id = -1;
		}
		champ->id = (int)id;
	}
	else
		champ->id = -1;
	ft_at_exit_ptr(free, champ, "Freeing champion");
	log_debug(__func__, "Create a new champion '%s' with predefined id '%d'",
		path, champ->id);
	return (champ);
}

int			vm_load_champions(t_vm *vm, int ac, char **av)
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
			champ = vm_new_champ(str_id, av[i]);
			if (!vm_read_champion(champ, av[i])
			|| !vm_store_champ(vm, champ, storage))
				return (0);
			str_id = NULL;
		}
	}
	vm_setup_champ_ids(vm, storage);
	log_trace(__func__, "Successfully load '%zu' champions", vm->champ_size);
	return (1);
}
