#ifndef VM_STRUCT_H
# define VM_STRUCT_H

# include "list.h"

typedef struct			s_header
{
	uint32_t			magic;
	int8_t				prog_name[PROG_NAME_LENGTH];
	uint32_t			nil1;
	uint32_t			prog_size;
	int8_t				comment[COMMENT_LENGTH];
	uint32_t			nil2;
}						t_header;

typedef struct			s_champ
{
	int					id;
	t_header			header;
	t_byte				code[CHAMP_MAX_SIZE + 1];
}						t_champ;

typedef struct			s_cursor
{
	int					id;
	t_op				*op;
	intptr_t			pc;
	intptr_t			step;
	intptr_t			args_pc[3];
	t_byte				args_types[3];
	int32_t				args[3];
	int32_t				reg[REG_NUMBER + 1];
	int					carry;
	int					live_cycle;
	int					cycles_to_exec;
	int					live_nbr;
	t_byte				mark;
}						t_cursor;

typedef struct			s_vm
{
	unsigned			config;
	t_byte				arena[MEM_SIZE];
	t_byte				marks[MEM_SIZE];
	t_champ				*champ[MAX_PLAYERS];
	size_t				champ_size;
	t_list				*cursors;
	int					dump_cycle;
	int					dump_byteness;
	int					cycles;
	int					cycles_after_check;
	int					cycles_to_die;
	int					lives_nbr;
	int					checks_nbr;
	int					last_alive;
}						t_vm;

#endif
