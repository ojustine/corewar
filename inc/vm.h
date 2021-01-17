#ifndef VM_H
# define VM_H

# include "op.h"
# include "logger.h"
# include <stdint.h>

# define	DEFAULT_DUMP_CYCLES		1500
# define	DEFAULT_DUMP_BYTENESS	32

enum					e_vm_flags
{
	VM_DUMP = (1U),
	VM_STEP = (1U << 1),
	VM_AFF = (1U << 2),
	VM_VERBOSE = (1U << 3)
};

typedef struct		s_header
{
	uint32_t		magic;
	uint8_t			prog_name[PROG_NAME_LENGTH];
	uint32_t		null1;
	uint32_t		prog_size;
	uint8_t			comment[COMMENT_LENGTH];
	uint32_t		null2;
}					t_header;

typedef struct			s_champ
{
	int32_t			id;
	t_header		header;
	int32_t			code_size;
	uint8_t			*code;
	size_t			last_live;
}						t_champ;

typedef struct			s_carriage
{
	uint32_t			id;
	t_bool				carry;
	uint8_t				op_code;
	ssize_t				last_live;
	int					cycles_to_exec;
	uint8_t				args_types[3];
	int32_t				pc;
	uint32_t			step;
	int32_t				reg[REG_NUMBER];
	t_champ				*player;
	struct s_carriage	*next;
}						t_carriage;

typedef struct	s_vm
{
	unsigned	flags;
	int			dump_cycles;
	int			dump_byteness;
	int			cycles;
	int			option_v[4];
	int			option_g[2];
	int			opt_num;
	int			check_nbr;
	char		*players[MAX_PLAYERS + 1];
	t_champ		champ[MAX_PLAYERS];
//	t_array		processes;
	int			process_index;
	int			champ_size;
	int			last_dead_champ;
	int			winner;
}				t_vm;

#endif
