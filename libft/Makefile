NAME := libft.a

ARRAYPATH:= array_list/
ARRAY:= arrlist_new arrlist_pop arrlist_util arrlisti_peek  arrlisti_push  \
        arrlist_peek arrlist_push arrlisti_new arrlisti_pop arrlisti_utils

BITWISEPATH:= conv/
BITWISE:= hasbyte mask operations shift

CONVPATH:= conv/
CONV:= ft_atol ft_uitoa_dec ft_uitoa_hex ft_ultoa_base ft_ultoa_hex

HASHMAPPATH:= hash_map/
HASHMAP:= hash_map_destroy hash_map_get hash_map_iterate hash_map_new \
            hash_map_put hash_map_resize hash_map_utils

IOPATH:= io/
IO:= ft_putendl get_next_line ft_putstr ft_putnbr

PRINTFPATH:= io/ft_printf/
PRINTF:= buffered_printer float_processing float_processing_ag \
         float_processing_ef float_processing_fast_dtoa \
         float_processing_fast_ldtoa float_processing_fxd_dbl \
         ft_printf_ ft_printf_alias  ft_printf_utils \
         get_format_arg number_processing string_processing

LOGGERPATH:= logger/
LOGGER:= logger logger_appenders logger_config logger_log logger_log_alias

LISTPATH:= list/
LIST:= list_clear list_new list_pop list_push

MEMPATH:= mem/
MEM:= memalloc memchr memcmp memcpy memmem memset memswap

STRINGPATH:= string/
STRING:= ft_chars_count ft_isint ft_strdup ft_strjoin ft_strndup ft_strsplit \
        ft_free_split ft_strchr ft_strequ ft_strlen ft_strnlen ft_words_count ft_strnequ \
        ft_concat ft_strany ft_strrev ft_wstrlen

UTILPATH:= util/
UTIL:= ft_assert ft_kill  ft_log_error

MATHPATH:= math/
MATH:= ft_min abs divmod max moddiv numlen pow sqrt

SYSTEMPATH:= system/
SYSTEM:= ft_path

CC:=gcc
OBJPATH:=obj/
SRCPATH:=src/
HPATH:=inc/
CFLAGS:=  -Wall -Wextra -Werror -I $(HPATH)


BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
CYAN:="\033[1;35m"
PURPLE:="\033[1;36m"
WHITE:="\033[1;37m"

FILES+=$(addprefix $(ARRAYPATH), $(ARRAY))
FILES+=$(addprefix $(BITWISEPATH), $(BITWISE))
FILES+=$(addprefix $(CONVPATH), $(CONV))
FILES+=$(addprefix $(HASHMAPPATH), $(HASHMAP))
FILES+=$(addprefix $(IOPATH), $(IO))
FILES+=$(addprefix $(PRINTFPATH), $(PRINTF))
FILES+=$(addprefix $(LOGGERPATH), $(LOGGER))
FILES+=$(addprefix $(LISTPATH), $(LIST))
FILES+=$(addprefix $(MEMPATH), $(MEM))
FILES+=$(addprefix $(STRINGPATH), $(STRING))
FILES+=$(addprefix $(UTILPATH), $(UTIL))
FILES+=$(addprefix $(MATHPATH), $(MATH))
FILES+=$(addprefix $(SYSTEMPATH), $(SYSTEM))

SRC:=$(addprefix $(SRCPATH), $(addsuffix .c, $(FILES)))
OBJ:=$(addprefix $(OBJPATH), $(addsuffix .o, $(FILES)))

CCHF:=.cache_exists

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(CYAN) " - Compiling $@"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo $(GREEN) " - Done"

$(OBJPATH)%.o: $(SRCPATH)%.c | $(CCHF)
	@$(CC) $(CFLAGS) -c $< -o $@

%.c:
	@echo $(RED) "Missing file : $@"

$(CCHF):
	@mkdir $(OBJPATH)
	@mkdir $(OBJPATH)$(ARRAYPATH)
	@mkdir $(OBJPATH)$(BITWISEPATH)
	@mkdir $(OBJPATH)$(CONVPATH)
	@mkdir $(OBJPATH)$(HASHMAPPATH)
	@mkdir $(OBJPATH)$(IOPATH)
	@mkdir $(OBJPATH)$(PRINTFPATH)
	@mkdir $(OBJPATH)$(LOGGERPATH)
	@mkdir $(OBJPATH)$(LISTPATH)
	@mkdir $(OBJPATH)$(MEMPATH)
	@mkdir $(OBJPATH)$(STRINGPATH)
	@mkdir $(OBJPATH)$(UTILPATH)
	@mkdir $(OBJPATH)$(MATHPATH)
	@mkdir $(OBJPATH)$(SYSTEMPATH)
	@touch $(CCHF)

clean:
	@rm -rf $(OBJPATH)
	@rm -f $(CCHF)

fclean: clean
	@rm -f $(NAME)

re: fclean
	@$(MAKE) all

norm:
	@echo $(RED)
	@norminette $(SRC) $(HPATH) | grep -v Norme -B1 || true

.PHONY: all clean fclean re test norme