NAME	=	minishell

SRC_DIR	=	src
OBJ_DIR	=	obj
LIBFT	=	incs/libft/libft.a
SRCS	=	$(addprefix $(SRC_DIR)/tokens/, checks.c token_utils.c tokens.c) \
			$(addprefix $(SRC_DIR)/parsing/, commands.c expand_utils.c parse_utils.c \
				expand.c put_results.c parse.c) \
			$(addprefix $(SRC_DIR)/, custom_error.c test_main.c free.c utils.c \
				paths.c pipes.c execution.c) \
			$(addprefix $(SRC_DIR)/builtins/, exit_cmd.c pwd_cmd.c cd_cmd.c env_cmd.c \
				builtin_utils.c echo_cmd.c export_cmd.c unset_cmd.c)
OBJ		=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))

INCS	=	-I incs/minishell.h -I incs/parse.h -I incs/libft/incs -I incs/builtins.h
CC		=	cc 
FLAGS	=   -Wall -Wextra -Werror
RM		=	rm -f

GREY_T	= \33[90m
WHITE_F = \e[7;37m
RESET 	= \033[0m

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
				@mkdir -p $(dir $@)
				@$(CC) $(RL) $(FLAGS) $(INCS) -c $< -o $@
				 @echo "$(GREY_T)compiled: $< into $@$(RESET)"

all:	$(NAME)

$(NAME):	$(OBJ)
			@make -C incs/libft -s
			@$(CC) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
			@echo "$(WHITE_F)MINISHELL BUILT SUCCESFULLY$(RESET)"


clean:
			@$(RM) $(OBJ)
			@$(RM) -r $(OBJ_DIR)
			@make clean -C incs/libft -s 
			@echo "$(GREY_T)*.o files & obj dir removed$(RESET)"

fclean:		clean
			@$(RM) $(NAME)
			@make fclean -C incs/libft -s
			@echo "$(GREY_T)all build artifacts removed$(RESET)"

re:			fclean all

.PHONY:	all clean fclean re
