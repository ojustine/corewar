#include "ft_printf.h"
#include "system.h"
#include "vm.h"

char		*vm_show_mem(intptr_t addr, char *buf, size_t size)
{
	register char	*ptr;
	register size_t	i;

	i = 0;
	ptr = buf;
	while (i < size && i < SHOW_MEM_MAX)
	{
		if (addr >= MEM_SIZE)
			addr = 0;
		ptr += ft_sprintf(ptr, "%02x ", g_vm.arena[addr++]);
		i++;
	}
	*ptr = '\0';
	return (buf);
}

intptr_t	vm_trunc(intptr_t addr)
{
	addr %= MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	return (addr);
}

void		vm_mark_mem(t_byte mark, intptr_t addr, size_t size)
{
	size_t	tail_size;
	size_t	head_size;

	addr = vm_trunc(addr);
	log_trace(__func__, "Mark %zu bytes addressed %P with %#08b",
			  size, addr, mark);
	if (addr + size <= MEM_SIZE)
		ft_memset(&g_vm.marks[addr], mark, size);
	else
	{
		tail_size = MEM_SIZE - addr;
		head_size = addr + size - MEM_SIZE;
		ft_memset(&g_vm.marks[addr], mark, tail_size);
		ft_memset(&g_vm.marks[0], mark, head_size);
	}
}

void		vm_store_mem(int32_t val, intptr_t addr, size_t size)
{
	size_t	tail_size;
	size_t	head_size;

	log_trace(__func__, "Store %zu bytes (%#b) at address %P",
			  size, val, addr);
	addr = vm_trunc(addr);
	to_endian(FT_BIG_ENDIAN, &val, REG_SIZE);
	if (addr + size <= MEM_SIZE)
		ft_memcpy(&g_vm.arena[addr], &val, size);
	else
	{
		tail_size = MEM_SIZE - addr;
		head_size = addr + size - MEM_SIZE;
		ft_memcpy(&g_vm.arena[addr], &val, tail_size);
		ft_memcpy(&g_vm.arena[0], (t_byte *)&val + tail_size, head_size);
	}
}

int32_t		vm_load_mem(intptr_t addr, size_t size)
{
	register size_t	i;
	int32_t			res;

	addr = vm_trunc(addr);
	i = 0;
	res = 0;
	if (addr + size <= MEM_SIZE)
		if (size < 3)
			res = size == 1 ? g_vm.arena[addr] : *((int16_t*)&g_vm.arena[addr]);
		else
			res = *((int32_t*)&g_vm.arena[addr]);
	else
		while (++i <= size)
		{
			if (addr == MEM_SIZE)
				addr = 0;
			res += (int32_t)g_vm.arena[addr] << ((size - i) * 8);
			addr++;
		}
	to_sys_endian(FT_BIG_ENDIAN, &res, size);
	log_trace(__func__, "Load %zu bytes (%#b) from address %P",
		size, res, addr);
	return (res);
}
