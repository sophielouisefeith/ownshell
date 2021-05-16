
NAME = minishell

LIB = minishell.a

LIBFT = libft

SRC =  srcs/main.c\
		srcs/builtin/cd.c\
		srcs/builtin/echo.c\
		srcs/builtin/env.c\
		srcs/builtin/exit.c\
		srcs/builtin/export.c\
		srcs/builtin/export_utils.c\
		srcs/builtin/ft_split2.c\
		srcs/builtin/pwd.c\
		srcs/builtin/unset.c\
		srcs/execute/check_builtin_again.c\
		srcs/execute/check_specials_utils.c\
		srcs/execute/check_specials.c\
		srcs/execute/env_ll_to_array.c\
		srcs/execute/execute_builtin.c\
		srcs/execute/execute_utils.c\
		srcs/execute/execute.c\
		srcs/execute/get_path.c\
		srcs/execute/parameter_expansion_utils.c\
		srcs/execute/parameter_expansion.c\
		srcs/lexer/lexer_utils.c\
		srcs/lexer/lexer.c\
		srcs/lexer/ll_make_list_lexer.c\
		srcs/parser/free_parser.c\
		srcs/parser/input.c\
		srcs/parser/ll_make_list_parser.c\
		srcs/parser/output.c\
		srcs/parser/parser_utils.c\
		srcs/parser/parser.c\
		srcs/utils/character_check.c\
		srcs/utils/character_check2.c\
		srcs/utils/error_utils.c\
		srcs/utils/error.c\
		srcs/utils/free.c\
		srcs/utils/save_env.c\
		srcs/utils/signals.c\
		srcs/utils/utils_general.c\
		libft/get_next_line/get_next_line.c\
		libft/get_next_line/get_next_line_utils.c\

RESET			= 	\033[0m
GREEN 			= 	\033[38;5;46m
WHITE 			= 	\033[38;5;15m
GREY 			= 	\033[38;5;8m
ORANGE 			= 	\033[38;5;202m
RED 			= 	\033[38;5;160m

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

INCL = includes

all: $(NAME)

$(NAME): $(OBJ) lib_ft
	@ar rcs $(LIB) $(OBJ)
	@gcc $(CFLAGS) $(LIB) -o $(NAME)
	@echo "\n>>>>>Finished making<<<<<"
	@echo " $(ORANGE) run : ./minishell	-> now your in the bash run any bash command $(RESET)"

lib_ft:
	@echo "\n>>>>>Making lib_ft<<<<<"
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(LIB)

%.o: %.c
	@echo $@
	@gcc $(CFLAGS) -I$(INCL) -c $< -o $@
	

clean:
	@$(RM) $(OBJ)
	@make clean -C $(LIBFT)
	
fclean: clean
	@$(RM) $(LIB) $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
