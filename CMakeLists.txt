cmake_minimum_required(VERSION 3.17)
project(corewar C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS " -Wall -Wextra -Wshadow -pedantic")

include_directories(inc libft/inc)

add_library(libft STATIC
		libft/inc/ft_printf.h
		libft/inc/array_list.h
		libft/inc/conv.h
		libft/inc/hash_map.h
		libft/inc/io_.h
		libft/inc/list.h
		libft/inc/math.h
		libft/inc/mem.h
		libft/inc/str.h
		libft/inc/util.h
		libft/inc/logger.h
		libft/inc/error.h
		libft/inc/system.h
        libft/src/array_list/arrlist_new.c
        libft/src/array_list/arrlist_peek.c
        libft/src/array_list/arrlist_pop.c
        libft/src/array_list/arrlist_push.c
        libft/src/array_list/arrlist_util.c
        libft/src/array_list/arrlisti_new.c
        libft/src/array_list/arrlisti_peek.c
        libft/src/array_list/arrlisti_pop.c
        libft/src/array_list/arrlisti_push.c
        libft/src/array_list/arrlisti_utils.c
        libft/src/conv/ft_atol.c
        libft/src/hash_map/hash_map_destroy.c
        libft/src/hash_map/hash_map_get.c
        libft/src/hash_map/hash_map_iterate.c
        libft/src/hash_map/hash_map_new.c
        libft/src/hash_map/hash_map_put.c
        libft/src/hash_map/hash_map_resize.c
        libft/src/hash_map/hash_map_utils.c
        libft/src/io/ft_putendl.c
        libft/src/io/ft_putnbr.c
        libft/src/io/ft_putstr.c
        libft/src/io/get_next_line.c
        libft/src/list/list_clear.c
        libft/src/list/list_new.c
        libft/src/list/list_pop.c
        libft/src/list/list_push.c
		libft/src/math/min.c
		libft/src/math/abs.c
		libft/src/math/max.c
		libft/src/math/divmod.c
		libft/src/math/moddiv.c
		libft/src/math/pow.c
		libft/src/math/sqrt.c
		libft/src/math/numlen.c
        libft/src/mem/memalloc.c
        libft/src/mem/memchr.c
        libft/src/mem/memcmp.c
        libft/src/mem/memcpy.c
        libft/src/mem/memmem.c
        libft/src/mem/memset.c
        libft/src/mem/memswap.c
        libft/src/string/ft_chars_count.c
        libft/src/string/ft_free_split.c
        libft/src/string/ft_isint.c
        libft/src/string/ft_strchr.c
        libft/src/string/ft_strdup.c
        libft/src/string/ft_strequ.c
        libft/src/string/ft_strnequ.c
        libft/src/string/ft_strjoin.c
        libft/src/string/ft_strlen.c
        libft/src/string/ft_strndup.c
        libft/src/string/ft_strnlen.c
        libft/src/string/ft_strsplit.c
        libft/src/string/ft_words_count.c
		libft/src/string/ft_concat.c
		libft/src/string/ft_strany.c
		libft/src/string/ft_strrev.c
		libft/src/string/ft_wstrlen.c
		libft/src/string/ft_strstart.c
		libft/src/string/ft_strend.c
        libft/src/util/ft_assert.c
        libft/src/util/ft_kill.c
        libft/src/util/ft_log_error.c
		libft/src/util/ft_exit.c
		libft/src/system/ft_path.c
		libft/src/system/endian.c
		libft/src/system/byte_swap_unsigned.c
		libft/src/system/byte_swap_signed.c
		libft/src/logger/logger_.h
		libft/src/logger/logger.c
		libft/src/logger/logger_appenders.c
		libft/src/logger/logger_config.c
		libft/src/logger/logger_log.c
		libft/src/logger/logger_log_alias.c
        libft/src/conv/ft_atol.c
		libft/src/conv/ft_ultoa_base.c
		libft/src/conv/ft_uitoa_dec.c
		libft/src/conv/ft_uitoa_hex.c
		libft/src/conv/ft_ultoa_hex.c
		libft/inc/bitwise.h
		libft/src/bitwise/hasbyte.c
		libft/src/bitwise/mask.c
		libft/src/bitwise/operations.c
		libft/src/bitwise/shift.c
		libft/src/io/ft_printf/buffered_printer.c
		libft/src/io/ft_printf/float_processing.c
		libft/src/io/ft_printf/float_processing_ag.c
		libft/src/io/ft_printf/float_processing_ef.c
		libft/src/io/ft_printf/float_processing_fast_ldtoa.c
		libft/src/io/ft_printf/float_processing_fast_dtoa.c
		libft/src/io/ft_printf/float_processing_fxd_dbl.c
		libft/src/io/ft_printf/ft_printf_alias.c
		libft/src/io/ft_printf/ft_printf_.c
		libft/src/io/ft_printf/ft_printf_.h
		libft/src/io/ft_printf/ft_printf_const_data.h
		libft/src/io/ft_printf/ft_printf_utils.c
		libft/src/io/ft_printf/get_format_arg.c
		libft/src/io/ft_printf/number_processing.c
		libft/src/io/ft_printf/string_processing.c

        libft/src/util/ft_log_error.c

		libft/inc/predicates.h
		libft/src/predicates/ft_isalnum.c
		libft/src/predicates/ft_isalpha.c
		libft/src/predicates/ft_isascii.c
		libft/src/predicates/ft_isdigit.c
		libft/src/predicates/ft_isprint.c
		libft/src/predicates/ft_isspace.c

		libft/src/string/ft_strtrim.c libft/src/string/strbuilder.c libft/src/string/strbuilder_.h)

set_target_properties(libft PROPERTIES PUBLIC_HEADER
        libft/inc/array_list.h
        libft/inc/conv.h
        libft/inc/hash_map.h
		libft/inc/io_.h
        libft/inc/list.h
        libft/inc/math.h
        libft/inc/mem.h
        libft/inc/str.h
        libft/inc/util.h)

add_executable(corewar $<TARGET_OBJECTS:libft>
		inc/op.h inc/op_struct.h
		inc/vm.h src/vm/vm_options.c src/vm/vm_champion_load.c src/vm/vm_champion_read.c src/vm/vm_print.c src/vm/vm_options_logger.c src/vm/vm_run.c src/vm/vm_cursor.c src/vm/vm_exec.c src/vm/vm_memory_access.c inc/vm_struct.h src/op/op_live.c src/op/op_ld.c src/op/op_st.c src/op/op_and.c src/op/op_sub.c src/op/op_add.c src/op/util.c src/op/op_or.c src/op/op_xor.c src/op/op_zjmp.c src/op/op_ldi.c src/op/op_sti.c src/op/op_fork.c src/op/op_lld.c src/op/op_lldi.c src/op/op_lfork.c src/vm/vm_verbose.c src/vm/vm_check.c src/op/op_aff.c)