#include <unistd.h>
#include "system.h"
#include "util.h"
#include "error.h"
#include "vm.h"

int	vm_verify_champ_header(t_champ *champ)
{
	log_trace(__func__, "Verify header fields");
	if (champ->header.magic != COREWAR_EXEC_MAGIC)
	{
		log_error(__func__, "Champion '%s': invalid magic number: %#X",
			champ->header.prog_name, champ->header.magic);
		return (0);
	}
	if (champ->header.prog_size > CHAMP_MAX_SIZE)
	{
		log_error(__func__, "Champion '%s': invalid code size: %d",
			champ->header.prog_name, champ->header.prog_size);
		return (0);
	}
	if (champ->header.nil1 || champ->header.nil2)
	{
		log_error(__func__, "Champion '%s': no control nulls: 1: %x, 2: %x",
			champ->header.prog_name, champ->header.nil1, champ->header.nil2);
		return (0);
	}
	return (1);
}

int	vm_read_champ_header(t_champ *champ, int fd)
{
	const size_t	hsize = sizeof(t_header);
	int				reads;

	log_trace(__func__, "Read champion's header");
	reads = read(fd, &champ->header, hsize);
	log_debug(__func__, "Reads header: %d bytes", reads);
	if (reads == -1)
	{
		log_error(__func__, "Read error: %m");
		return (0);
	}
	if (reads != (int)hsize)
	{
		log_error(__func__, "Reads doesn't match header size: %d vs %zu",
			reads, hsize);
		return (0);
	}
	to_sys_endian(FT_BIG_ENDIAN, &champ->header.magic, 4);
	to_sys_endian(FT_BIG_ENDIAN, &champ->header.prog_size, 4);
	return (vm_verify_champ_header(champ));
}

int	vm_read_champ_code(t_champ *champ, int fd)
{
	const size_t	csize = champ->header.prog_size;
	int				reads;

	log_trace(__func__, "Read champion's exec code");
	reads = read(fd, &champ->code, CHAMP_MAX_SIZE + 1);
	log_debug(__func__, "Reads exec code: %d bytes", reads);
	if (reads == -1)
	{
		log_error(__func__, "Read error: %m");
		return (0);
	}
	if (reads > CHAMP_MAX_SIZE)
	{
		log_error(__func__, "Reads exceed max code size: %d", CHAMP_MAX_SIZE);
		return (0);
	}
	if (reads != (int)csize)
	{
		log_error(__func__, "Reads doesn't match code size: %d vs %zu",
			reads, csize);
		return (0);
	}
	return (1);
}

int	vm_read_champion(t_champ *champ, const char *path)
{
	int fd;

	ft_assert(champ != NULL, __func__, E_NULL_PTR);
	log_trace(__func__, "Start reading champion from '%s'", path);
	fd = open(path, O_RDONLY, 0200);
	if (fd == -1)
	{
		log_error(__func__, "Cannot open file '%s': %m", path);
		return (0);
	}
	if (!vm_read_champ_header(champ, fd) || !vm_read_champ_code(champ, fd))
	{
		log_error(__func__, "Read champion failed");
		return (0);
	}
	close(fd);
	log_trace(__func__, "Successfully reads champion '%s'",
		champ->header.prog_name);
	return (1);
}
