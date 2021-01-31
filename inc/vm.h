#ifndef VM_H
# define VM_H

# include "op.h"
# include "op_struct.h"
# include "mem.h"
# include "list.h"
# include "logger.h"
# include <stdint.h>

# define	COR_EXT				".cor"
# define	DUMP_BYTENESS		32
# define OP_CODE_LEN	1
# define ARGS_CODE_LEN	1
# define REG_LEN		1

enum					e_vm_flags
{
	VM_VERBOSE_LIVE = (1U),
	VM_VERBOSE_CYCLE = (1U << 1),
	VM_VERBOSE_OP = (1U << 2),
	VM_VERBOSE_DEATH = (1U << 3),
	VM_VERBOSE_MOVE = (1U << 4),
	VM_DUMP = (1U << 5),
	VM_STEP = (1U << 6),
	VM_AFF = (1U << 7),
	VM_COLOR = (1U << 8)
};

typedef struct					s_header
{
	uint32_t					magic;
	int8_t						prog_name[PROG_NAME_LENGTH];
	uint32_t					nil1;
	uint32_t					prog_size;
	int8_t						comment[COMMENT_LENGTH];
	uint32_t					nil2;
}								t_header;

typedef struct			s_champ
{
	t_header		header;
	t_byte			code[CHAMP_MAX_SIZE + 1];
	int				id;
	int				last_live;
}						t_champ;

typedef struct			s_cursor
{
	int					id;
	t_op				op;
	int					carry;
	t_byte				op_code;
	int					last_live;
	int					cycles_to_exec;
	t_byte				args_types[3];
	int					pc;
	int					step;
	t_byte				reg[REG_NUMBER + 1];
	t_champ				*parent;
}						t_cursor;

typedef struct	s_vm
{
	unsigned	config;
	int			dump_cycles;
	int			dump_byteness;
	t_byte		arena[MEM_SIZE];
	t_byte		marks[MEM_SIZE];
	t_champ		*champ[MAX_PLAYERS];
	size_t		champ_size;
	t_list		*cursors;
	int			cycles;
	int			cycles_after_check;
	int			opt_num;
	int			check_nbr;
	int			process_index;
	int			last_dead_champ;
	int			last_alive;
}				t_vm;

int	vm_options(t_vm *vm, int ac, char **av);
int	vm_load_champions(t_vm *vm, int ac, char **av);
int	vm_read_champion(t_champ *champ, const char *path);
t_cursor	*vm_cursor_new(t_champ *parent, int pc);
void		vm_cursor_set_initial(t_vm *vm);
void	vm_run(t_vm *vm);
void	vm_exec(t_vm *vm);
void	vm_eval(t_vm *vm, t_cursor *cursor);

#endif
