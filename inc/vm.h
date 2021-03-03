#ifndef VM_H
# define VM_H

# include <stdint.h>
# include "op.h"
# include "op_struct.h"
# include "vm_struct.h"
# include "mem.h"
# include "list.h"
# include "logger.h"

# define	COR_EXT				".cor"
# define	DUMP_BYTENESS		32
# define	SHOW_MEM_MAX		16
# define OP_CODE_LEN	1
# define ARGS_CODE_LEN	1
# define REG_SELF_SIZE	1
# define IND_SELF_SIZE	2

enum					e_vm_flags
{
	VM_VERBOSE_LIVE = (1U),
	VM_VERBOSE_CYCLE = (1U << 1),
	VM_VERBOSE_OP = (1U << 2),
	VM_VERBOSE_DEATH = (1U << 3),
	VM_VERBOSE_MOVE = (1U << 4),
	VM_DUMP = (1U << 5),
	VM_STEP_DUMP = (1U << 6),
	VM_AFF = (1U << 7),
	VM_COLOR = (1U << 8)
};

t_vm					g_vm;

int	vm_options(int ac, char **av);
int	vm_load_champions(int ac, char **av);
int	vm_read_champion(t_champ *champ, const char *path);
t_cursor	*vm_cursor_new(intptr_t pc);
void		vm_cursor_set_initial(void);
void		vm_cursor_move(t_cursor *cursor);

intptr_t	vm_trunc(intptr_t addr);
int32_t	vm_load_mem(intptr_t addr, size_t size);
void	vm_store_mem(int32_t val, intptr_t addr, size_t size);
void	vm_mark_mem(t_byte mark, intptr_t addr, size_t size);
char		*vm_show_mem(intptr_t addr, char *buf, size_t size);

void	vm_exec(t_cursor *cursor);
void	vm_check(void);

int32_t	get_arg_value(t_cursor *cursor, int index, int is_mod);

void		print_intro(void);
void		print_arena(void);
void		print_winner(void);

void	verbose_move_pc(intptr_t pc, intptr_t step);
void	verbose_cycle(void);
void	verbose_cycles_to_die(void);
void	verbose_cursor_death(t_cursor *cursor);
#endif
