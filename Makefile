NAME	=	minishell

SRC_DIR	=	src
OBJ_DIR	=	.obj
LIBFT	=	incs/libft/libft.a
SRCS	=	$(addprefix $(SRC_DIR)/token/, checks.c token_utils.c tokens.c) \
			$(addprefix $(SRC_DIR)/parse/, commands.c expand_utils.c parse_utils.c \
				expand.c output.c parse.c) \
			$(addprefix $(SRC_DIR)/io_handling/, paths.c pipes.c pipe_utils.c \
				redirect.c heredoc.c) \
			$(addprefix $(SRC_DIR)/builtins/, exit_cmd.c pwd_cmd.c cd_cmd.c env_cmd.c \
				builtin_utils.c echo_cmd.c export_cmd.c unset_cmd.c) \
			$(addprefix $(SRC_DIR)/, main.c signal.c custom_error.c utils.c execution.c)
OBJ		=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))

INCS	=	-I incs/minishell.h -I incs/parse.h -I incs/libft/incs -I incs/builtins.h
CC		=	cc
FLAGS	=   -Wall -Wextra -Werror
RM		=	rm -f

GREY_T	= \33[90m
GREEN_T	= \33[92m
ORANG_T	= \33[93m
RED_T	= \33[91m
BLUE_T	= \33[94m

RED_B	= \33[1;91m
GREEN_B	= \33[1;92m
ORANG_B	= \33[1;93m
GREY_B	= \33[1;90m
BLUE_B	= \33[1;94m
WHITE_B	= \33[1;97m

WHITE_F = \33[7;37m
RESET 	= \033[0m

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
				@mkdir -p $(dir $@)
				@$(CC) $(RL) $(FLAGS) $(INCS) -c $< -o $@
				@echo "[$(GREEN_T)OK$(RESET)]$(GREY_T): $< $@$(RESET)"

all:	$(NAME)

$(NAME):	$(OBJ)
			@make -C incs/libft -s
			@$(CC) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
			@echo "$(WHITE_B)MINISHELL BUILT SUCCESFULLY!$(RESET)"


clean:
			@$(RM) $(OBJ)
			@$(RM) -r $(OBJ_DIR)
			@make clean -C incs/libft -s
			@echo "$(ORANG_T)*.o files & obj dir removed$(RESET)"

fclean:		clean
			@$(RM) $(NAME)
			@make fclean -C incs/libft -s
			@echo "$(RED_T)all build artifacts removed$(RESET)"

re:			fclean all

.PHONY:	all clean fclean re
