NAME := libft.a

ARRAYPATH:= array_list/
ARRAY:= arrlist_new arrlist_pop arrlist_util arrlisti_peek  arrlisti_push  \
        arrlist_peek arrlist_push arrlisti_new arrlisti_pop arrlisti_utils

CONVPATH:= conv/
CONV:= ft_atol

HASHMAPPATH:= hash_map/
HASHMAP:= hash_map_destroy hash_map_get hash_map_iterate hash_map_new \
            hash_map_put hash_map_resize hash_map_utils

IOPATH:= io/
IO:= ft_putendl get_next_line ft_putstr ft_putnbr

LISTPATH:= list/
LIST:= list_clear list_new list_pop list_push

MEMPATH:= mem/
MEM:= memalloc memchr memcmp memcpy memmem memset memswap

STRINGPATH:= string/
STRING:= ft_chars_count ft_isint ft_strdup ft_strjoin ft_strndup ft_strsplit \
        ft_free_split ft_strchr ft_strequ ft_strlen ft_strnlen ft_words_count

UTILPATH:= util/
UTIL:= ft_assert ft_kill  ft_log_error

MATHPATH:= math/
MATH:= ft_min

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
FILES+=$(addprefix $(CONVPATH), $(CONV))
FILES+=$(addprefix $(HASHMAPPATH), $(HASHMAP))
FILES+=$(addprefix $(IOPATH), $(IO))
FILES+=$(addprefix $(LISTPATH), $(LIST))
FILES+=$(addprefix $(MEMPATH), $(MEM))
FILES+=$(addprefix $(STRINGPATH), $(STRING))
FILES+=$(addprefix $(UTILPATH), $(UTIL))
FILES+=$(addprefix $(MATHPATH), $(MATH))

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
	@mkdir $(OBJPATH)$(CONVPATH)
	@mkdir $(OBJPATH)$(HASHMAPPATH)
	@mkdir $(OBJPATH)$(IOPATH)
	@mkdir $(OBJPATH)$(LISTPATH)
	@mkdir $(OBJPATH)$(MEMPATH)
	@mkdir $(OBJPATH)$(STRINGPATH)
	@mkdir $(OBJPATH)$(UTILPATH)
	@mkdir $(OBJPATH)$(MATHPATH)
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