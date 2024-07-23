NAME	=	minishell

SRC_DIR	=	src
OBJ_DIR	=	obj
LIBFT	=	incs/libft/libft.a
SRCS	=	$(addprefix $(SRC_DIR)/tokens/, checks.c token_utils.c tokens.c) \
			$(addprefix $(SRC_DIR)/parsing/, commands.c expand_utils.c parse_utils.c \
				expand.c put_results.c parse.c) \
			$(addprefix $(SRC_DIR)/, custom_error.c command_path.c test_main.c)
OBJ		=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))

INCS	=	-I incs/parse.h -I incs/libft/incs
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

GREY_T	= \33[90m
WHITE_F = \e[7;37m
RESET 	= \033[0m

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
				@mkdir -p $(dir $@)
				@$(CC) $(FLAGS) $(INCS) -c $< -o $@
				 @echo "$(GREY_T)compiled: $< into $@$(RESET)"

all:	$(NAME)

$(NAME):	$(OBJ)
			@make -C incs/libft -s
			@$(CC) $(OBJ) $(LIBFT) -o $(NAME)
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
